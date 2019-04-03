#include "Receiver.h"
#include "Argument_data.h"
#include "String_Manager.h"
#include <cstring>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

//==API==//
void Receiver::Receive_data(const int &client_id, const Argument_data &data) {

  //1.make the proper_dir
  char* root_dir_name = Create_dir_for_sender_in_mirror(client_id,data.getMirror_dir_name());
  //2.open the fifo;
  const int fifo_fd = fifo_handler.Open_fifo(client_id,data);
  //




  //2. deallocate

}



//==CONSTRUCTOR-DESTRUCTOR===//

Receiver::Receiver(Error_Handler_Interface *handler,Fifo_pipe_handler fifo_handler,Read_Write_handler read_write_handler) : handler(handler),fifo_handler(fifo_handler),read_write_handler(read_write_handler) {}

Receiver::~Receiver() {
  delete handler;
}

//==INNER-FUNCTIONALITY==//

char * Receiver::Create_dir_for_sender_in_mirror(const int &client_id, const char *mirror_dir_path_name) {

  //1.construct the dir name;
  char* new_dir_name = Construct_new_dir_path_name(client_id,mirror_dir_path_name);
  //2.make the dir
  mkdir(new_dir_name,0777);
  return new_dir_name;


}

char *Receiver::Construct_new_dir_path_name(const int &client_id, const char *mirror_dir_path_name) {

  char* new_dir_path_name;
  char client_id_buffer[20];
  sprintf(client_id_buffer,"%d",client_id_buffer);

  new_dir_path_name=String_Manager::Allocate(strlen(mirror_dir_path_name)+strlen(client_id_buffer)+2);
  sprintf(new_dir_path_name,"%s/%s",mirror_dir_path_name,client_id_buffer);
  return new_dir_path_name;

}









