#ifndef PROJ_2_ARGUMENTS_VALIDATOR_H
#define PROJ_2_ARGUMENTS_VALIDATOR_H

#include "Error_handler_interface.h"
#include "Argument_data.h"

class Arguments_Validator {
 private:
  Error_Handler_Interface* handler;
  //==INNER FUNCTIONALLITY==//
  bool Check_for_directory(const char* dir_name);
  void Make_mirror_dir(const char* mirror_dir_name);
  void Make_common_dir(const char *common_dir_name);
  void Mirror_dir_check(const Argument_data &data);
  void Input_dir_check(const Argument_data &data);
  void Common_check_and_create(const Argument_data &data);


 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  explicit Arguments_Validator(Error_Handler_Interface* handler);
  ~Arguments_Validator();

  //==API==//
  void Validate_Arguments(Argument_data data);


};

#endif //PROJ_2_ARGUMENTS_VALIDATOR_H
