#include "Syncronizer.h"
#include "Factory.h"
#include "Log_file_handler.h"
#include "Status_Record.h"
#include <unistd.h>
#include <signal.h>
#include <wait.h>

//==CONSTRUCTOR-DESTRUCTOR==//
Syncronizer::Syncronizer(const common_dir_monitor &monitor,const Sender &sender,const Receiver &receiver,const Deleter &deleter,Error_Handler_Interface *handler,Cleaner *cleaner,Signal_handler *sig_handler)
    : monitor(monitor), sender(sender), receiver(receiver), deleter(deleter),cleaner(cleaner),sig_handler(sig_handler) {
  this->handler = handler;
}

Syncronizer::~Syncronizer() {
  delete handler;
  delete cleaner;
  delete sig_handler;
}

//==API==//
void Syncronizer::Syncronize(const Argument_data &data) {

  while(true) {
    // get two arrays one with the new ids and one with the ids that left
    Clients_List **changes_array = monitor.update(data.getCommon_dir_name(), data.getId());
    handle_new_clients(changes_array[0], data,Factory::Create_Status_Record());
    handle_removed_clients(changes_array[1],data);
    Deallocate_array(changes_array);
    sleep(5);
    std::cout<<"woke up"<<std::endl;
  }

}

//==INNER-FUNCTIONALLITY==//
void Syncronizer::Deallocate_array(Clients_List **array) {

  for(int i =0;i<2;i++){
    delete array[i];
  }
  delete[] array;

}

void Syncronizer::handle_new_clients(Clients_List *added_clients, const Argument_data &data, Status_Record record) {

  //initialize the fd for the signals
  sig_handler->Init_signalfd();
  // set up the recors
  record.Allocate_arrays(added_clients->Get_length());

  // for each new client start a sender and a receiver
 for(Client_list_node* current=added_clients->getHead();current!=NULL;current=current->getNext()){

    int sender_id =sender.Send_data(current->getId(), data, Log_file_handler(data.getLog_file_name(),data.getId()));
    record.Insert_sender(sender_id,current->getId());

    int receiver_id = receiver.Receive_data(current->getId(), data, Log_file_handler(data.getLog_file_name(),data.getId()));
    record.Insert_receiver(receiver_id,current->getId());
  }


  Wait_for_children(data, &record);
  sig_handler->Close_fd();
}

void Syncronizer::Wait_for_children(const Argument_data &data, Status_Record *record) {
  // wail all the childer are done
  while (!record->Check_if_done()) {
    pid_t child_id;
    int status;

    // if a child proccess ends
    child_id = wait(&status);
    if (WEXITSTATUS(status)) {
      // it ended succesfully
      Child_finished(*record, child_id);
    } else
      //if it ended with a problem get its signal
      Handle_Signal_from_children(record, data);
  }
}

void Syncronizer::Child_finished(Status_Record &record, const int &child_id) const {
  int index;
  if (record.Search_for_child_id_in_senders_and_receivers(child_id, &index)) {
    std::cout << "Sender finished successfully"<<std::endl;
    record.Set_sender_to_finished(index);
  }
  else {
    std::cout << "Receiver finished successfully" << std::endl;
    record.Set_receiver_to_finished(index);
  }
}

void Syncronizer::handle_removed_clients(Clients_List *removed_clients, const Argument_data &data) {

  // for each client that left delete the its contents from mirror
  for(Client_list_node* current=removed_clients->getHead();current!=NULL; current=current->getNext()){
    deleter.Delete_client_left(current->getId(), data, Log_file_handler(data.getLog_file_name(), data.getId()));
  }

}

void Syncronizer::Error_in_child(Status_Record *record, Signal_received &last_sig, const Argument_data &data) {
  int index;

  // check if it was a sender or a receiver based on the child id
  if(record->Search_for_child_id_in_senders_and_receivers(last_sig.Get_Pid(),&index))
    Start_new_sender_if_possible(data,record,index);
  else
    Start_new_receier_if_possible(data,record,index);
}

void Syncronizer::Start_new_sender_if_possible(const Argument_data &data, Status_Record *record, const int &index) {

  if(!record->can_retry_sender(index))
    return;

  int new_sender =sender.Send_data(record->get_clinet_from_sender(index),data,Log_file_handler(data.getLog_file_name(),data.getId()));
  record->update_sender(index,new_sender);
}

void Syncronizer::Start_new_receier_if_possible(const Argument_data &data, Status_Record *record, const int &index) {
  deleter.Delete_directory(record->get_clinet_from_receiver(index),data);

  if(!record->can_retry_receiver(index))
    return;

  int new_receiver = receiver.Receive_data(record->get_clinet_from_receiver(index),data,Log_file_handler(data.getLog_file_name(),data.getId()));
  record->update_receiver(index,new_receiver);
}

void Syncronizer::Handle_Signal_from_children(Status_Record *record, const Argument_data &data) {

    Signal_received last_sig = sig_handler->Get_next_signal();

    if(last_sig.Get_Signal()==SIGUSR1){
      //find if it was a sender or a receiver and get the index
      Error_in_child(record,last_sig,data);
    }
}
