#ifndef PROJ_2_ERROR_HANDLER_H
#define PROJ_2_ERROR_HANDLER_H

#include "Error_handler_interface.h"

class Error_Handler:public Error_Handler_Interface{
 public:
  void Terminating_Error(const char *message) override;
  void Common_Eroor(const char *message) override;
};

#endif //PROJ_2_ERROR_HANDLER_H
