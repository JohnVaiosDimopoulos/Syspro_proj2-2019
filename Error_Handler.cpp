#include "Error_Handler.h"
#include <iostream>

void Error_Handler::Terminating_Error(const char *message) {
  std::cout<<message<<std::endl;
  exit(0);
}

void Error_Handler::Common_Eroor(const char *message) {
  std::cout<<message<<std::endl;
}


