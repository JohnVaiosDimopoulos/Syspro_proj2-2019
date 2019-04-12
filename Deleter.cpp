#include <iostream>
#include "Deleter.h"
#include "String_Manager.h"
#include "Argument_data.h"

//==CONSTRUCTOR-DESTRUCTOR==//

Deleter::Deleter(Error_Handler_Interface *handler, Cleaner cleaner)
    : handler(handler), cleaner(cleaner) {}

Deleter::~Deleter() {
  delete handler;
}

//==API==//
void Deleter::Delete(const int &client_id, const Argument_data& data,Log_file_handler log_file_handler) {
  char* dir_to_delete = Construct_dir_to_delete_path(data.getMirror_dir_name(),client_id);
  cleaner.Delete_dir(dir_to_delete);
  free(dir_to_delete);
  log_file_handler.Log_Client_left(client_id);
}

char *Deleter::Construct_dir_to_delete_path(const char *mirror_dir_path_name, const int &client_id) {
  char client_id_buf[20];
  sprintf(client_id_buf,"%d",client_id);

  char* new_path = String_Manager::Allocate((strlen(mirror_dir_path_name)+strlen(client_id_buf)+2));
  sprintf(new_path,"%s/%s",mirror_dir_path_name,client_id_buf);
  return new_path;

}
