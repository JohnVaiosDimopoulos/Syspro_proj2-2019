#ifndef PROJ_2_SYNCRONIZER_H
#define PROJ_2_SYNCRONIZER_H
#include "Factory.h"
#include "common_dir_monitor.h"
#include "Sender.h"
#include "Receiver.h"
#include "Deleter.h"
#include "Argument_data.h"

class Syncronizer {

 private:
  common_dir_monitor monitor;
  Sender sender;
  Receiver receiver;
  Deleter deleter;
  Error_Handler_Interface* handler;

  //==INNER-FUNCTIONALITY==//
  void Deallocate_array(Clients_List** array);
  void handle_new_clients(Clients_List *added_clients, const Argument_data &data);
  void handle_removed_clients(Clients_List *removed_clients, const Argument_data &data);

 public:
  //==API==//
  void Syncronize(const Argument_data& data);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Syncronizer(const common_dir_monitor &monitor,const Sender &sender,const Receiver &receiver,const Deleter &deleter,Error_Handler_Interface* handler);
  ~Syncronizer();

};

#endif //PROJ_2_SYNCRONIZER_H
