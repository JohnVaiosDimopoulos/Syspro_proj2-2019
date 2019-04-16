#ifndef PROJ_2_FACTORY_H
#define PROJ_2_FACTORY_H

#include "Error_Handler.h"
#include "child_status.h"
class Argument_Manager;
class Arguments_Validator;
class Cleaner;
class Client_initalizer;
class Clients_List;
class common_dir_monitor;
class Syncronizer;
class Sender;
class Receiver;
class Deleter;
class Fifo_pipe_handler;
class Read_Write_handler;
class Log_file_handler;
class Signal_handler;
class Status_Record;

class Factory {

 public:
  static Error_Handler * Create_Error_Handler();
  static Argument_Manager Create_Argument_Manager();
  static Arguments_Validator Create_Argument_Validator();
  static Cleaner* Create_cleaner();
  static Client_initalizer Create_Initializer();
  static Clients_List Create_List();
  static Clients_List* Create_List_in_heap();
  static common_dir_monitor Create_common_state();
  static Syncronizer Create_Syncronizer();
  static Sender Create_Sender();
  static Receiver Create_Receiver();
  static Deleter Create_Deleter();
  static Fifo_pipe_handler * Create_fifo_handler();
  static Read_Write_handler * Create_read_write_handler();
  static Signal_handler* Create_Signalfd_handler();
  static Status_Record Create_Status_Record();
};

#endif //PROJ_2_FACTORY_H
