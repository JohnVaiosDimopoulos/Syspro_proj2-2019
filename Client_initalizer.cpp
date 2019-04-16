#include "Client_initalizer.h"
#include "Argument_Manager.h"
#include "Arguments_Validator.h"
#include "Argument_data.h"
#include "String_Manager.h"
#include "Factory.h"
#include "Cleaner.h"
#include <signal.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
char* my_mirror_dir;
char* my_id_file;

void Client_initalizer::Write_id_file_in_common_dir(const char *common_dir_name,int id) {
  // construct the pathname
  char file_path_buffer[200];
  sprintf(file_path_buffer,"%s/%d.id",common_dir_name,id);

  //allocate the space
  my_id_file=String_Manager::Allocate_and_copy(file_path_buffer);

  //make the file
  std::fstream id_file;
  id_file.open(file_path_buffer,std::fstream::out);
  id_file<<getppid();
  id_file.close();
}

Argument_data Client_initalizer::Initialize(int argc,char **argv,Argument_Manager manager,Arguments_Validator validator) {

  // get arguments and validate them
  Argument_data data = manager.Manage(argc,argv);
  validator.Validate_Arguments(data);
  //we write the clients .id file in common dir
  Write_id_file_in_common_dir(data.getCommon_dir_name(),data.getId());
  // get up signal handlers for SIGINT and SIGQUIT
  Set_up_global_var(data);
  Set_up_signal_handler();

  return data;
}

void Client_initalizer::Set_up_global_var(const Argument_data& data) {
  my_mirror_dir =String_Manager::Allocate_and_copy(data.getMirror_dir_name());
}

void Client_initalizer::sig_handler(int signum) {
  Cleaner* cleaner=Factory::Create_cleaner();
  cleaner->clean(my_mirror_dir,my_id_file);
  delete cleaner;
  exit(-1);
}

void Client_initalizer::Set_up_signal_handler() {
  signal(SIGINT,sig_handler);
  signal(SIGQUIT,sig_handler);
}

