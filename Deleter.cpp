#include "Deleter.h"

//==CONSTRUCTOR-DESTRUCTOR==//

Deleter::Deleter(Error_Handler_Interface *handler) : handler(handler) {}

Deleter::~Deleter() {
  delete handler;

}

//==API==//
void Deleter::Delete(const int &client_id) {

}
