#include "Argument_data.h"
#include "String_Manager.h"
#include <cstring>

//====CONSTRUCTOR-DESTRUCTOR===//

Argument_data::Argument_data(){
  this->common_dir_name=NULL;
  this->mirror_dir_name=NULL;
  this->log_file_name=NULL;
  this->input_dir_name=NULL;
}

Argument_data::~Argument_data() {
  free(common_dir_name);
  free(mirror_dir_name);
  free(input_dir_name);
  free(log_file_name);
}

//===GETTERS-SETTERS==//

char *Argument_data::getCommon_dir_name() const {
  return common_dir_name;
}

void Argument_data::setCommon_dir_name(char *common_dir_name) {
  if(this->common_dir_name!=NULL)
    free(this->common_dir_name);
  this->common_dir_name = String_Manager::Allocate_and_copy(common_dir_name);
}

char *Argument_data::getInput_dir_name() const {
  return input_dir_name;
}

void Argument_data::setInput_dir_name(char *input_dir_name) {
  if(this->input_dir_name!=NULL)
    free(this->input_dir_name);
  this->input_dir_name = String_Manager::Allocate_and_copy(input_dir_name);
}

char *Argument_data::getMirror_dir_name() const {
  return mirror_dir_name;
}

void Argument_data::setMirror_dir_name(char *mirror_dir_name) {
  if(this->mirror_dir_name!=NULL)
    free(this->mirror_dir_name);
  this->mirror_dir_name = String_Manager::Allocate_and_copy(mirror_dir_name);
}

char *Argument_data::getLog_file_name() const {
  return log_file_name;
}

void Argument_data::setLog_file_name(char *log_file_name) {
  if(this->log_file_name!=NULL)
    free(this->log_file_name);
  this->log_file_name = String_Manager::Allocate_and_copy(log_file_name);
}

void Argument_data::setId(int id) {
  Argument_data::id = id;
}

const int Argument_data::getId() const {
  return id;
}

void Argument_data::setBuffer_size(int buffer_size) {
  Argument_data::buffer_size = buffer_size;
}

const int Argument_data::getBuffer_size() const {
  return buffer_size;
}




