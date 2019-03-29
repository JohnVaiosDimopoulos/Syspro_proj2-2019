#ifndef PROJ_2_ERROR_HANDLER_INTERFACE_H
#define PROJ_2_ERROR_HANDLER_INTERFACE_H

class Error_Handler_Interface{
 public:
  virtual void Terminating_Error(const char* message) = 0;
  virtual void Common_Eroor(const char* message) =0;

};

#endif //PROJ_2_ERROR_HANDLER_INTERFACE_H
