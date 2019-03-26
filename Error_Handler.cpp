#include "Error_Handler.h"
#include <iostream>

void Error_Handler::Terminating_Error(const char *message) {
  std::cout<<message<<std::endl;
  exit(-1);
}
