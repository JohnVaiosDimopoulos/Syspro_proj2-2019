#include "Fifo_pipe_handler.h"
#include "Argument_data.h"
#include "String_Manager.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

//==CONSTRUCTOR-DESTRUCTOR==//
Fifo_pipe_handler::Fifo_pipe_handler(Error_Handler_Interface *handler,Read_Write_handler* read_write_handler) : error_handler(handler),read_write_handler(read_write_handler),fifo_path_name(NULL),fifo_fd(-1),buffer_size(-1) {}



Fifo_pipe_handler::~Fifo_pipe_handler() {
  delete error_handler;
  delete read_write_handler;
  free(fifo_path_name);
}



//==API==//

void Fifo_pipe_handler::Make_and_open_fifo(const int &receiver_id, const Argument_data &data) {

  fifo_path_name = Construct_fifo_name_for_sender(receiver_id, data);
  Make_fifo(fifo_path_name);
  fifo_fd= Get_fifo_fd_for_sender(fifo_path_name);

  this->buffer_size = data.getBuffer_size();
}

void Fifo_pipe_handler::Open_fifo_at_receiver_non_blocking(const int &client_id, const Argument_data &data) {

  fifo_path_name = Construct_fifo_name_for_receiver(client_id, data);
  fifo_fd= Get_fifo_fd_for_receiver(fifo_path_name);
  this->buffer_size = data.getBuffer_size();

}

void Fifo_pipe_handler::Write_in_fifo_with_custom_buffer_size(size_t buffer_size, const void *buffer) {
  read_write_handler->Write_and_check(this->fifo_fd,buffer,buffer_size);

}

bool Fifo_pipe_handler::Read_in_fifo_with_custom_buffer_size_with_timeout(size_t buffer_size, void *buffer) {
  return read_write_handler->Read_and_check_with_timeout(this->fifo_fd,buffer,buffer_size);

}

int Fifo_pipe_handler::Get_buffer_size() {
  return this->buffer_size;
}

void Fifo_pipe_handler::Close_fifo() {
  close(this->fifo_fd);
}

void Fifo_pipe_handler::Delete_fifo() {
  std::cout<<"deleting fifo"<<std::endl;
  if(remove(fifo_path_name)==-1){
    std::cout<<"failed to remove fifo"<<std::endl;
  }
}

void Fifo_pipe_handler::Set_to_Non_blocking() {
  fcntl(this->fifo_fd,F_SETFD,O_NONBLOCK);
}



//==INNER-FUNCTIONALITY==//

void Fifo_pipe_handler::Make_fifo(const char *fifo_name) {

  if (mkfifo(fifo_name, 0666) == -1)
    error_handler->Terminating_Error("FAILED TO MAKE FIFO PIPE");

}

char *Fifo_pipe_handler::Construct_fifo_name_for_receiver(const int &sender_id, const Argument_data &data) {
  int pipe_path_size = Calculate_pipe_path_size(sender_id, data);
  char *fifo_name_buffer = String_Manager::Allocate(pipe_path_size);
  sprintf(fifo_name_buffer, "%s/%d_to_%d.fifo", data.getCommon_dir_name(),sender_id,data.getId());
  return fifo_name_buffer;
}

char *Fifo_pipe_handler::Construct_fifo_name_for_sender(const int &receiver_id, const Argument_data &data) {

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
  int size = 11;
  size+=strlen(data.getCommon_dir_name());
  size+=strlen(receiver_id_buffer);
  size+=strlen(sender_id_buffer);

  return size;
}

int Fifo_pipe_handler::Get_fifo_fd_for_sender(const char *fifo_name) {

  int fifo_pipe_fd;
    if ((fifo_pipe_fd = open(fifo_name,O_WRONLY))==-1) {
        perror("error");
        error_handler->Terminating_Error("FAILED TO OPEN FIFO PIPE IN THE SENDER");
    }
    return fifo_pipe_fd;

}

int Fifo_pipe_handler::Get_fifo_fd_for_receiver(const char *fifo_name) {

  int fifo_pipe_fd;
  bool wait = true;
  while (wait) {
    if ((fifo_pipe_fd = open(fifo_name, O_RDONLY)) == -1) {
      if(errno==2)
        continue;
      std::cout<<errno<<std::endl;
      perror("error");
      error_handler->Terminating_Error("FAILED TO OPEN FIFO PIPE IN THE RECEIVER");
    }
    return fifo_pipe_fd;
  }


}










