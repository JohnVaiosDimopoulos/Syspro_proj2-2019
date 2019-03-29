#include "Client_initalizer.h"
#include "Argument_Manager.h"
#include "Arguments_Validator.h"
#include "Argument_data.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

void Client_initalizer::Write_id_file_in_common_dir(const char *common_dir_name,int id) {
  char file_path_buffer[200];
  sprintf(file_path_buffer,"%s/%d.id",common_dir_name,id);

  std::fstream id_file;
  id_file.open(file_path_buffer,std::fstream::out);
  id_file<<getppid();
  id_file.close();
}

Argument_data Client_initalizer::Initialize(int argc,char **argv,Argument_Manager manager,Arguments_Validator validator) {

  Argument_data data = manager.Manage(argc,argv);
  validator.Validate_Arguments(data);
  Write_id_file_in_common_dir(data.getCommon_dir_name(),data.getId());
  return data;
}
