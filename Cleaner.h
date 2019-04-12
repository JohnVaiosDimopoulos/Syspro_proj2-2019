#ifndef PROJ_2_CLEANER_H
#define PROJ_2_CLEANER_H

#include "Error_handler_interface.h"

class Argument_data;

class Cleaner {

 private:
  Error_Handler_Interface* handler;
  void Delete_from_common(const char* common_file_name,const int id);



 public:
  //===CONSTRUCTOR-DESTRUCTOR==//
  Cleaner(Error_Handler_Interface* handler);
  ~Cleaner();
  void Delete_dir(const char *current_dir_name);
  void clean(const Argument_data &data);


};

#endif //PROJ_2_CLEANER_H
