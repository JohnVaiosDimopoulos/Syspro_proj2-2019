#include "Syncronizer.h"
#include <unistd.h>

//==CONSTRUCTOR-DESTRUCTOR==//
Syncronizer::Syncronizer(const common_dir_monitor &monitor,const Sender &sender,const Receiver &receiver,const Deleter &deleter,Error_Handler_Interface* handler)
    : monitor(monitor), sender(sender), receiver(receiver), deleter(deleter) {
  this->handler = handler;
}

Syncronizer::~Syncronizer() {
  delete handler;
}

//==API==//
void Syncronizer::Syncronize(const Argument_data &data) {

  while(true) {
    Clients_List **changes_array = monitor.update(data.getCommon_dir_name(), data.getId());
    handle_new_clients(changes_array[0]);
    handle_removed_clients(changes_array[1]);
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

void Syncronizer::handle_new_clients(Clients_List *added_clients) {

  for(Client_list_node* current=added_clients->getHead();current!=NULL;current=current->getNext()){
    sender.Send_data(current->getId());
    receiver.Receive_data(current->getId());
  }

}

void Syncronizer::handle_removed_clients(Clients_List *removed_clients) {

  for(Client_list_node* current=removed_clients->getHead();current!=NULL; current=current->getNext()){
    deleter.Delete(current->getId());
  }

}
