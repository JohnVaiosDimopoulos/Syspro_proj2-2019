#include "Fifo_pipe_handler.h"
#include "Argument_data.h"
#include "String_Manager.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

//==CONSTRUCTOR-DESTRUCTOR==//
Fifo_pipe_handler::Fifo_pipe_handler(Error_Handler_Interface *handler) : handler(handler) {}



//==API==//

int Fifo_pipe_handler::Make_and_open_fifo(const int &receiver_id, const Argument_data &data) {

  char *fifo_name_buffer = Construct_fifo_name(receiver_id, data);
  Make_fifo(fifo_name_buffer);
  int fifo_pipe_fd = Open_fifo_from_name(fifo_name_buffer);

  return fifo_pipe_fd;
}

int Fifo_pipe_handler::Open_fifo(const int &client_id, const Argument_data &data) {

  char * fifo_name = Construct_fifo_name(client_id,data);
  int fifo_fd=Open_fifo_from_name(fifo_name);
  return fifo_fd;

}

//==INNER-FUNCTIONALITY==//

void Fifo_pipe_handler::Make_fifo(const char *fifo_name) {

  if (mkfifo(fifo_name, 0666) == -1)
    handler->Terminating_Error("FAILED TO MAKE FIFO PIPE");

}

char *Fifo_pipe_handler::Construct_fifo_name(const int &receiver_id, const Argument_data &data) {

  int pipe_path_size = Calculate_pipe_path_size(receiver_id, data);
  char *fifo_name_buffer = String_Manager::Allocate(pipe_path_size);
  sprintf(fifo_name_buffer, "%s/%d_to_%d.fifo", data.getCommon_dir_name(), data.getId(), receiver_id);
  return fifo_name_buffer;

}

int Fifo_pipe_handler::Calculate_pipe_path_size(const int &receiver_id, const Argument_data &data) {

  // the string is common_dir_path/serder_id_to_receiver_id.fifo
  // the constant characters in the string are 10;
  char receiver_id_buffer[20],sender_id_buffer[20];
  sprintf(receiver_id_buffer,"%d",receiver_id);
  sprintf(sender_id_buffer,"%d",data.getId());
  int size = 10;
  size+=strlen(data.getCommon_dir_name());
  size+=strlen(receiver_id_buffer);
  size+=strlen(sender_id_buffer);

  return size;
}

int Fifo_pipe_handler::Open_fifo_from_name(const char *fifo_name) {

  int fifo_pipe_fd;
  if ((fifo_pipe_fd = open(fifo_name, O_RDWR)) < 0)
    handler->Terminating_Error("FAILED TO OPEN FIFO PIPE IN THE SENDER");
  return fifo_pipe_fd;

}


