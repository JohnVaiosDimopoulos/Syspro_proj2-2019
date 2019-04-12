#include "Syncronizer.h"
#include "Factory.h"
#include "Log_file_handler.h"
#include "Status_Record.h"
#include <unistd.h>
#include <signal.h>

//==CONSTRUCTOR-DESTRUCTOR==//
Syncronizer::Syncronizer(const common_dir_monitor &monitor,const Sender &sender,const Receiver &receiver,const Deleter &deleter,Error_Handler_Interface *handler,const Cleaner &cleaner,const Signalfd_handler &sig_handler)
    : monitor(monitor), sender(sender), receiver(receiver), deleter(deleter),cleaner(cleaner),sig_handler(sig_handler) {
  this->handler = handler;
}

Syncronizer::~Syncronizer() {
  delete handler;
}

//==API==//
void Syncronizer::Syncronize(const Argument_data &data) {

  while(true) {
    Clients_List **changes_array = monitor.update(data.getCommon_dir_name(), data.getId());
    handle_new_clients(changes_array[0], data,Factory::Create_Status_Record());
    handle_removed_clients(changes_array[1],data);
    Deallocate_array(changes_array);
    sleep(5);
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

  sig_handler.Init();
  record.Allocate_arrays(added_clients->Get_length());

  for(Client_list_node* current=added_clients->getHead();current!=NULL;current=current->getNext()){

    int sender_id =sender.Send_data(current->getId(), data, Log_file_handler(data.getLog_file_name(),data.getId()));
    record.Insert_sender(sender_id,current->getId());

    int receiver_id = receiver.Receive_data(current->getId(), data, Log_file_handler(data.getLog_file_name(),data.getId()));
    record.Insert_receiver(receiver_id,current->getId());
  }

  while (!record.Check_if_done()){
    Signal_received last_sig = sig_handler.Get_next_signal();
    if(last_sig.Get_Signal()==SIGINT || last_sig.Get_Signal()==SIGQUIT){
      cleaner.clean(data);
      exit(-1);
    }

    else if(last_sig.Get_Signal()==SIGUSR1){
      //find if it was a sender or a receiver and get the index
      int index;
      if(record.Search_for_child_id_in_senders_and_receivers(last_sig.Get_Pid(),&index)){
        int new_sender =sender.Send_data(record.get_clinet_from_sender(index),data,Log_file_handler(data.getLog_file_name(),data.getId()));
        record.update_sender(index,new_sender);
      } else{
        int new_receiver = receiver.Receive_data(record.get_clinet_from_receiver(index),data,Log_file_handler(data.getLog_file_name(),data.getId()));
        record.update_receiver(index,new_receiver);
      }
      //TODO make the check for the 3 errors and refactor
    }


  }



  sig_handler.Close_fd();
}

void Syncronizer::handle_removed_clients(Clients_List *removed_clients, const Argument_data &data) {

  for(Client_list_node* current=removed_clients->getHead();current!=NULL; current=current->getNext()){
    deleter.Delete(current->getId(),data,Log_file_handler(data.getMirror_dir_name(),data.getId()));
  }

}
