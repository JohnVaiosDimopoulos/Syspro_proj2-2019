#include <iostream>
#include "Factory.h"


int main(int argc,char** argv){

  Argument_Manager manager = Factory::Create_Argument_Manager();
  Argument_data data = manager.Manage(argc,argv);
  Arguments_Validator validator = Factory::Create_Argument_Validator();
  validator.Validate_Arguments(data);
}