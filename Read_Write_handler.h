#ifndef PROJ_2_READ_WRITE_HANDLER_H
#define PROJ_2_READ_WRITE_HANDLER_H

#include "Error_handler_interface.h"
#include "Factory.h"
#include <iostream>

class Read_Write_handler {
 private:
  Error_Handler_Interface* handler;
 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  Read_Write_handler(Error_Handler_Interface *handler);
  virtual ~Read_Write_handler();

  Read_Write_handler&operator=(Read_Write_handler src){
    this->handler=Factory::Create_Error_Handler();
  }

  //==API==//
  int Write_and_check(const int &file_desc, const void *buffer, const size_t &size);
  bool Read_and_check_no_timeout(const int &file_desc, void *buffer, const size_t &size);
  bool Read_and_check_with_timeout(const int &fle_desc, void *buffer, const size_t &size);



};

#endif //PROJ_2_READ_WRITE_HANDLER_H
