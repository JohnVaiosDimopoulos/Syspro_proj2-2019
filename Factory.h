#ifndef PROJ_2_FACTORY_H
#define PROJ_2_FACTORY_H

#include "Argument_Manager.h"
#include "Error_Handler.h"
#include "Arguments_Validator.h"

class Factory {

 public:
  static Error_Handler * Create_Error_Handler();
  static Argument_Manager Create_Argument_Manager();
  static Arguments_Validator Create_Argument_Validator();

};

#endif //PROJ_2_FACTORY_H
