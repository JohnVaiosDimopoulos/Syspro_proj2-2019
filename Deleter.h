#ifndef PROJ_2_DELETER_H
#define PROJ_2_DELETER_H
#include "Error_handler_interface.h"

class Deleter {
 private:
  Error_Handler_Interface* handler;
 public:

  //==API==/
  void Delete(const int& client_id);

  //==CONSTRUCTOR-DESTTRUCTOR==//
  Deleter(Error_Handler_Interface *handler);
  ~Deleter();

};

#endif //PROJ_2_DELETER_H
