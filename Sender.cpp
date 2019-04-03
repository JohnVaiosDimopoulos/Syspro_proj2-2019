#include "Sender.h"
#include "Argument_data.h"
#include "String_Manager.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>

//==CONSTRUCTOR-DESTRUCTOR==//
Sender::Sender(Error_Handler_Interface *handler, Fifo_pipe_handler fifo_handler,Read_Write_handler read_write_handler) : handler(handler),fifo_handler(fifo_handler),read_write_handler(read_write_handler) {}

Sender::~Sender() {
  delete handler;
}

//==API==//
void Sender::Send_data(const int &client_id, const Argument_data &data) {

  // the parent gets value different than 0 and it returns
  if(do_fork())
    return;

  // the child proccess continues;
  //Preparation
  int fifo_pipe_fd = fifo_handler.Make_and_open_fifo(client_id,data);
  DIR* input_dir_ptr = Open_dir(data.getInput_dir_name());
  //go through the input_dir recursively
  Recursively_go_Through_dir_and_send(NULL, data.getInput_dir_name(), fifo_pipe_fd,data.getBuffer_size());
  //write 00 to let the receiver know that the input is done
  Mark_end_of_input(fifo_pipe_fd);
  //close the pipe
  close(fifo_pipe_fd);
}

//==INNER-FUNCTIONALITY==//

void Sender::Mark_end_of_input(const int &fifo_pipe_fd) {
  write(fifo_pipe_fd,00,sizeof(u_int16_t));
}

pid_t Sender::do_fork() {

  pid_t  pid;
  if((pid=fork()==-1))
    handler->Terminating_Error("fork_failed");
  return pid;

}

DIR * Sender::Open_dir(const char *input_dir_name) {

  DIR* dir_ptr;
  if((dir_ptr=opendir(input_dir_name))==NULL)
    handler->Terminating_Error("FAILED TO OPEN INPUT DIR IN THE SENDRER");

  return dir_ptr;
}

void Sender::Recursively_go_Through_dir_and_send(const char *current_path_relative_to_input_dir,const char *current_dir_full_path,const int &fifo_pipe_fd,const int &pipe_buffer) {


  DIR* current_dir_ptr = Open_dir(current_dir_full_path);
  std::cout<<"IN DIR : "<<current_dir_full_path<<std::endl;
  struct dirent* current_dir;
  while ((current_dir=readdir(current_dir_ptr))!=NULL){

    //ignore hidden_files;
    if (current_dir->d_name[0]=='.')
      continue;

    struct stat stat_buf;
    char* full_path_name = create_full_path_name(current_dir_full_path, current_dir->d_name);
    Check_and_stat(&stat_buf,full_path_name);

    if(Is_file(&stat_buf)){
      //1.construct the relative to input dir path_name
      char *file_path_name_relative_to_input =create_path_name_relative_to_input(current_path_relative_to_input_dir, current_dir->d_name);
      //2.send the file
      Send_through_pipe(full_path_name,file_path_name_relative_to_input,fifo_pipe_fd,pipe_buffer);
      Deallocate_strings(full_path_name, file_path_name_relative_to_input);
      continue;
    }
    if(Is_Dir(&stat_buf)){
      //1.construct the relative to input_path
      char *dir_path_name_relative_to_input =create_path_name_relative_to_input(current_path_relative_to_input_dir, current_dir->d_name);
      //2.call recursively
      Recursively_go_Through_dir_and_send(dir_path_name_relative_to_input,full_path_name,fifo_pipe_fd,pipe_buffer);
      Deallocate_strings(full_path_name, dir_path_name_relative_to_input);
    }
  }

  closedir(current_dir_ptr);
}

void Sender::Deallocate_strings(char *full_path_name, char *path_name_relative_to_input) const {
  free(full_path_name);
  free(path_name_relative_to_input);
}

char * Sender::create_path_name_relative_to_input(const char *path_relative_to_input_dir, char *file_name) {

  char* path_to_return;
  if(path_relative_to_input_dir==NULL){
    path_to_return = String_Manager::Allocate_and_copy(file_name);
    return path_to_return;
  }

  path_to_return= String_Manager::Allocate(strlen(path_relative_to_input_dir)+strlen(file_name)+2);
  sprintf(path_to_return,"%s/%s",path_relative_to_input_dir,file_name);
  return path_to_return;

}

char * Sender::create_full_path_name(const char *current_dir_name, const char *file_name) {

  char* path_to_return = String_Manager::Allocate(strlen(current_dir_name)+strlen(file_name)+2);
  sprintf(path_to_return,"%s/%s",current_dir_name,file_name);
  return path_to_return;
}

void Sender::Check_and_stat(struct stat *stat_buf, const char *full_path_name) {

  if(stat(full_path_name,stat_buf)==-1)
    handler->Terminating_Error("stat failed in sender");
}

bool Sender::Is_file(struct stat *stat_buf) {
  if((stat_buf->st_mode&S_IFMT)==S_IFREG)
    return true;
  return false;

}

bool Sender::Is_Dir(struct stat *stat_buf) {
  if((stat_buf->st_mode & S_IFMT)==S_IFDIR)
    return true;
  return false;
}

void Sender::Send_through_pipe(const char *full_file_path,const char *file_path_relative_to_input,const int &fifo_pipe_fd,const int &pipe_buffer) {

  struct stat stat_buf;

  Check_and_stat(&stat_buf,full_file_path);
  u_int32_t file_size = stat_buf.st_size;
  u_int16_t file_name_size = strlen(file_path_relative_to_input)+1;
  //write file name size and name_relative to path
  read_write_handler.Write_and_check(fifo_pipe_fd,&file_name_size, sizeof(u_int16_t));
  read_write_handler.Write_and_check(fifo_pipe_fd,file_path_relative_to_input,file_name_size);
  //write file size
  read_write_handler.Write_and_check(fifo_pipe_fd,&file_size, sizeof(u_int32_t));
  int file_fd = open(full_file_path,O_RDONLY);
  // start reading file contents and write them in the pipe
  Read_from_file_and_write_in_pipe(fifo_pipe_fd, pipe_buffer, file_fd,file_size);
}

size_t Sender::Read_from_file_and_write_in_pipe(const int &fifo_pipe_fd,const int &fifo_buffer_size,const int &input_file_fd,const u_int32_t &file_size) {

  u_int32_t bytes_left_to_send = file_size;
  int buffer_size = fifo_buffer_size;
  char buffer[fifo_buffer_size];
  size_t  read_ret_value;

  while (read_write_handler.Read_and_check(input_file_fd,buffer,buffer_size)){
    read_write_handler.Write_and_check(fifo_pipe_fd,buffer,buffer_size);
    bytes_left_to_send=Caluculate_bytes_left_to_send(bytes_left_to_send,&buffer_size);
  }


}

u_int32_t Sender::Caluculate_bytes_left_to_send(const u_int32_t &bytes_left_to_send, int* buffer_size) {
  u_int32_t new_bytes_left = bytes_left_to_send-(*buffer_size);
  if(new_bytes_left<(*buffer_size))
    *buffer_size = new_bytes_left;
  return new_bytes_left;
}










