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

Cleaner Factory::Create_cleaner() {
  return Cleaner(Create_Error_Handler());
}

Client_initalizer Factory::Create_Initializer() {
  return Client_initalizer();
}
Clients_List Factory::Create_List() {
  return Clients_List(Create_Error_Handler());
}

