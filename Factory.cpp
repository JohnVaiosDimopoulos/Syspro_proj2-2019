#include "Factory.h"

Error_Handler * Factory::Create_Error_Handler(){
  return new Error_Handler();
}

Argument_Manager Factory::Create_Argument_Manager() {
  return Argument_Manager(Create_Error_Handler());
}

Arguments_Validator Factory::Create_Argument_Validator() {
  return Arguments_Validator(Create_Error_Handler());
}
