#include "Receiver.h"

//==API==//
void Receiver::Receive_data(const int &client_id) {

}
//==CONSTRUCTOR-DESTRUCTORU===//

Receiver::Receiver(Error_Handler_Interface *handler) : handler(handler) {}

Receiver::~Receiver() {
  delete handler;
}
