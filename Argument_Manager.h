#ifndef PROJ_2_ARGUMENT_MANAGER_H
#define PROJ_2_ARGUMENT_MANAGER_H
#include "Argument_data.h"
#include "Error_handler_interface.h"


class Argument_Manager {

 private:
  //==FUNCTIONALITY==//
  void check_Args_number(int argc);
  Argument_data Go_through_and_set_arguments(int argc, char **argv);
  bool check_and_set_id(int* index,char** argv,Argument_data* data);
  bool check_and_set_common_dir(int* index,char** argv,Argument_data* data);
  bool check_and_set_mirror_dir(int* index,char** argv,Argument_data* data);
  bool check_and_set_input_dir(int* index,char** argv,Argument_data* data);
  bool check_and_set_log_file(int* index,char** argv,Argument_data* data);
  bool check_and_set_buffer_size(int* index,char** argv,Argument_data* data);
  Error_Handler_Interface* handler;

 public:

  //==API==//
  Argument_data Manage(int argc,char** argv);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Argument_Manager(Error_Handler_Interface* handler);
  ~Argument_Manager();
};

#endif //PROJ_2_ARGUMENT_MANAGER_H
