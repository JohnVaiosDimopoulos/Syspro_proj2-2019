#include "Argument_Manager.h"
#include <cstring>
#include <iostream>

//==CONSTRUCTOR-DESTRUCTOR==//

Argument_Manager::Argument_Manager(Error_Handler_Interface* handler) {
  this->handler = handler;
}

Argument_Manager::~Argument_Manager() {
  delete handler;
}

//===API===//

Argument_data Argument_Manager::Manage(int argc, char **argv) {

  check_Args_number(argc);
  Argument_data data = Go_through_and_set_arguments(argc, argv);
  return data;
}

//==INNER-FUNCTIONALITY==//

void Argument_Manager::check_Args_number(int argc) {
  if(argc!=13)
    handler->Terminating_Error("WRONG NUMBER OF ARGUMENTS");
}

Argument_data Argument_Manager::Go_through_and_set_arguments(int argc, char **argv) {

  Argument_data data;

  for(int i = 1;i<argc;i++){

    if(check_and_set_buffer_size(&i,argv,&data))
      continue;
    else if(check_and_set_common_dir(&i,argv,&data))
      continue;
    else if(check_and_set_id(&i,argv,&data))
      continue;
    else if(check_and_set_mirror_dir(&i,argv,&data))
      continue;
    else if(check_and_set_input_dir(&i,argv,&data))
      continue;
    else if(check_and_set_log_file(&i,argv,&data))
      continue;
    else
      handler->Terminating_Error("WRONG ARGUMENTS GIVEN");
  }
  return data;
}

bool Argument_Manager::check_and_set_id(int *index, char **argv, Argument_data *data) {

  if(!strcmp(argv[*index],"-n")){
    (*index)++;
    data->setId(atoi(argv[*index]));
    return true;
  }
  return false;
}

bool Argument_Manager::check_and_set_common_dir(int *index, char **argv, Argument_data *data) {

  if(!strcmp(argv[*index],"-c")){
    (*index)++;
    data->setCommon_dir_name(argv[*index]);
    return true;
  }
  return false;
}

bool Argument_Manager::check_and_set_mirror_dir(int *index, char **argv, Argument_data *data) {

  if(!strcmp(argv[*index],"-m")){
    (*index)++;
    data->setMirror_dir_name(argv[*index]);
    return true;
  }
  return false;
}

bool Argument_Manager::check_and_set_input_dir(int *index, char **argv, Argument_data *data) {

  if(!strcmp(argv[*index],"-i")){
    (*index)++;
    data->setInput_dir_name(argv[*index]);
    return true;
  }
  return false;
}

bool Argument_Manager::check_and_set_log_file(int *index, char **argv, Argument_data *data) {

  if(!strcmp(argv[*index],"-l")){
    (*index)++;
    data->setLog_file_name(argv[*index]);
    return true;
  }
  return false;
}

bool Argument_Manager::check_and_set_buffer_size(int *index, char **argv, Argument_data *data) {

  if(!strcmp(argv[*index],"-b")){
    (*index)++;
    data->setBuffer_size(atoi(argv[*index]));
    return true;
  }
  return false;
}

