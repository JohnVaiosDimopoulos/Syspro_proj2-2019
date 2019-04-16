#ifndef PROJ_2_DELETER_H
#define PROJ_2_DELETER_H
#include "Error_handler_interface.h"
#include "Log_file_handler.h"
#include "Cleaner.h"

class Deleter {
 private:
  Error_Handler_Interface* handler;
  Cleaner* cleaner;


  //==INNER-FUNCTIONALITY==//
  char* Construct_dir_to_delete_path(const char* mirror_dir_path_name,const int& client_id);
  bool do_fork();

 public:

  //==API==/
  void Delete_client_left(const int &client_id, const Argument_data &data, Log_file_handler log_file_handler);
  void Delete_directory(const int &client_id, const Argument_data &data);


  //==CONSTRUCTOR-DESTTRUCTOR==//
  Deleter(Error_Handler_Interface *handler, Cleaner *cleaner);
  ~Deleter();

};

#endif //PROJ_2_DELETER_H
