#ifndef PROJ_2_RECEIVER_H
#define PROJ_2_RECEIVER_H
#include "Error_handler_interface.h"

class Receiver {
 private:
  Error_Handler_Interface* handler;
 public:
  //==API==//
  void Receive_data(const int &client_id);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Receiver(Error_Handler_Interface *handler);
  virtual ~Receiver();

};

#endif //PROJ_2_RECEIVER_H
