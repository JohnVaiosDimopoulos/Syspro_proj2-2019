#include "Arguments_Validator.h"
#include <dirent.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>


#define  MIRROR_PERMS 0775
#define COMMON_PERMS 0777

//==CONSTRUCTOR-DESTRUCTOR==//

Arguments_Validator::Arguments_Validator(Error_Handler_Interface *handler) {
  this->handler = handler;
}

Arguments_Validator::~Arguments_Validator() {
  delete handler;
}

//==API==//
void Arguments_Validator::Validate_Arguments(Argument_data& data) {

  //1.input_dir_name does not exists => error and termination
  Input_dir_check(data);
  //2.mirror_dir_name exists =>error and termination
  Mirror_dir_check(data);
  //3.mirror_dir_name and common_dir_name do not exists => make them
  Make_mirror_dir(data.getMirror_dir_name());
  Common_check_and_create(data);
  //4.create log file(if already exists delete the old one)
  Make_log_file(data.getLog_file_name());
}

void Arguments_Validator::Common_check_and_create(const Argument_data &data) {
  if(!Check_for_directory(data.getCommon_dir_name()))
    Make_common_dir(data.getCommon_dir_name());
}

void Arguments_Validator::Input_dir_check(const Argument_data &data) {
  if(!Check_for_directory(data.getInput_dir_name()))
    handler->Terminating_Error("ERROR:input directory does not exists");
}

void Arguments_Validator::Mirror_dir_check(const Argument_data &data) {
  if(Check_for_directory(data.getMirror_dir_name()))
    handler->Terminating_Error("EROOR:mirror file already exists");
}

//==INNER FUNCTIONALITY==//

void Arguments_Validator::Make_mirror_dir(const char* mirror_dir_name) {

  if(mkdir(mirror_dir_name,MIRROR_PERMS)==-1)
    handler->Terminating_Error("ERROR:occured while creating mirror dir");
}

void Arguments_Validator::Make_common_dir(const char *common_dir_name) {

  if(mkdir(common_dir_name,COMMON_PERMS)==-1)
    handler->Terminating_Error("ERROR:occurred while creating common dir");

}

bool Arguments_Validator::Check_for_directory(const char *dir_name) {

  DIR* directory;
  if((directory=opendir(dir_name))==NULL)
    return false;
  closedir(directory);
  return true;
}

void Arguments_Validator::Make_log_file(const char *log_file_name) {

  std::fstream log_file;
  log_file.open(log_file_name,std::fstream::app);
  log_file.close();
}

