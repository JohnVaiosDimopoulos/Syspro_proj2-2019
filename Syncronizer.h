#ifndef PROJ_2_SYNCRONIZER_H
#define PROJ_2_SYNCRONIZER_H
#include "Factory.h"
#include "common_dir_monitor.h"
#include "Sender.h"
#include "Cleaner.h"
#include "Receiver.h"
#include "Deleter.h"
#include "Argument_data.h"
#include "Signal_handler.h"

class Syncronizer {

 private:
  common_dir_monitor monitor;
  Sender sender;
  Receiver receiver;
  Deleter deleter;
  Cleaner* cleaner;
  Error_Handler_Interface* handler;
  Signal_handler* sig_handler;

  //==INNER-FUNCTIONALITY==//
  void Deallocate_array(Clients_List** array);
  void handle_new_clients(Clients_List *added_clients, const Argument_data &data, Status_Record record);
  void handle_removed_clients(Clients_List *removed_clients, const Argument_data &data);
  void Child_finished(Status_Record &record, const int &child_id) const;
  void Error_in_child(Status_Record *record, Signal_received &last_sig, const Argument_data &data);
  void Start_new_sender_if_possible(const Argument_data &data, Status_Record *record, const int &index);
  void Start_new_receier_if_possible(const Argument_data &data, Status_Record *record, const int &index);
  void Handle_Signal_from_children(Status_Record *record, const Argument_data &data);

 public:
  //==API==//
  void Syncronize(const Argument_data& data);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Syncronizer(const common_dir_monitor &monitor,const Sender &sender,const Receiver &receiver,const Deleter &deleter,Error_Handler_Interface *handler,Cleaner *cleaner,Signal_handler *sig_handler);
  ~Syncronizer();

  void Wait_for_children(const Argument_data &data, Status_Record *record);
};

#endif //PROJ_2_SYNCRONIZER_H
