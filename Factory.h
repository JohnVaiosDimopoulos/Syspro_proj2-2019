#ifndef PROJ_2_FACTORY_H
#define PROJ_2_FACTORY_H

#include "Error_Handler.h"
#include "Arguments_Validator.h"
#include "Argument_Manager.h"
#include "Client_initalizer.h"
#include "Cleaner.h"
#include "Clients_List.h"


class Factory {

 public:
  static Error_Handler * Create_Error_Handler();
  static Argument_Manager Create_Argument_Manager();
  static Arguments_Validator Create_Argument_Validator();
  static Cleaner Create_cleaner();
  static Client_initalizer Create_Initializer();
  static Clients_List Create_List();

};

#endif //PROJ_2_FACTORY_H
