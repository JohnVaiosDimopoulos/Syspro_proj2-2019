#include "Sender.h"

//==CONSTRUCTOR-DESTRUCTOR==//
Sender::Sender(Error_Handler_Interface *handler) : handler(handler) {}

Sender::~Sender() {
  delete handler;
}

//==API==//
void Sender::Send_data(const int &client_id) {
  

}

//==INNER-FUNCTIONALITY==//

