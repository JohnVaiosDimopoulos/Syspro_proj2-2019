#ifndef PROJ_2_SENDER_H
#define PROJ_2_SENDER_H
#include "Error_handler_interface.h"

class Sender {
 private:
  Error_Handler_Interface* handler;
 public:

  //==API==//
  void Send_data(const int &client_id);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Sender(Error_Handler_Interface *handler);
  virtual ~Sender();

};

#endif //PROJ_2_SENDER_H
