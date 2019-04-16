#include "Factory.h"
#include "Arguments_Validator.h"
#include "Argument_Manager.h"
#include "Client_initalizer.h"
#include "Cleaner.h"
#include "Clients_List.h"
#include "common_dir_monitor.h"
#include "Sender.h"
#include "Receiver.h"
#include "Syncronizer.h"
#include "Deleter.h"
#include "Fifo_pipe_handler.h"
#include "Read_Write_handler.h"
#include "Log_file_handler.h"
#include "Signal_handler.h"
#include "Status_Record.h"

//we construct all the objects from here



Error_Handler * Factory::Create_Error_Handler(){
  return new Error_Handler();
}

Argument_Manager Factory::Create_Argument_Manager() {
  return Argument_Manager(Create_Error_Handler());
}

Arguments_Validator Factory::Create_Argument_Validator() {
  return Arguments_Validator(Create_Error_Handler());
}

Cleaner* Factory::Create_cleaner() {
  return new Cleaner(Create_Error_Handler());
}

Client_initalizer Factory::Create_Initializer() {
  return Client_initalizer();
}

Clients_List Factory::Create_List() {
  return Clients_List(Create_Error_Handler());
}


common_dir_monitor Factory::Create_common_state() {
  return common_dir_monitor(Create_Error_Handler(),Create_List());
}

Clients_List *Factory::Create_List_in_heap() {
  return new Clients_List(Create_Error_Handler());
}

Syncronizer Factory::Create_Syncronizer() {
  return Syncronizer(Create_common_state(),Create_Sender(),Create_Receiver(),Create_Deleter(),Create_Error_Handler(),Create_cleaner(),Create_Signalfd_handler());
}

Sender Factory::Create_Sender() {
  return Sender(Create_Error_Handler(), Create_fifo_handler(), Create_read_write_handler());
}

Receiver Factory::Create_Receiver() {
  return Receiver(Create_Error_Handler(), Create_fifo_handler(),Create_read_write_handler());
}

Deleter Factory::Create_Deleter() {
  return Deleter(Create_Error_Handler(), Create_cleaner());
}
Fifo_pipe_handler * Factory::Create_fifo_handler() {
  return new Fifo_pipe_handler(Create_Error_Handler(),Create_read_write_handler());
}

Read_Write_handler * Factory::Create_read_write_handler() {
  return new Read_Write_handler(Create_Error_Handler());
}

Signal_handler* Factory::Create_Signalfd_handler() {
  return new Signal_handler(Create_Error_Handler());
}

Status_Record Factory::Create_Status_Record() {
  return Status_Record(Create_Error_Handler());
}


