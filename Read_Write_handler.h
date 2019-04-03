#ifndef PROJ_2_READ_WRITE_HANDLER_H
#define PROJ_2_READ_WRITE_HANDLER_H

#include "Error_handler_interface.h"
#include <iostream>

class Read_Write_handler {
 private:
  Error_Handler_Interface* handler;
 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  Read_Write_handler(Error_Handler_Interface *handler);
  virtual ~Read_Write_handler();

  //==API==//
  int Write_and_check(const int &file_desc, const void *buffer, const size_t &size);
  bool Read_and_check(const int &file_desc, void *buffer, const size_t &size);



};

#endif //PROJ_2_READ_WRITE_HANDLER_H
