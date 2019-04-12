#include "Receiver.h"
#include "Argument_data.h"
#include "String_Manager.h"
#include <cstring>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

//==API==//
int Receiver::Receive_data(const int &client_id, const Argument_data &data, Log_file_handler log_file_handler) {

 int pid = do_fork();
 if(pid)
    return pid;

  //1.make the proper_dir
  char* root_dir_name = Create_dir_for_sender_in_mirror(client_id,data.getMirror_dir_name());
  //2.open the fifo;
  fifo_handler->Open_fifo_at_receiver_non_blocking(client_id, data);
  Get_input(root_dir_name,&log_file_handler);
  //send_succes signal;

  //2. deallocate
  fifo_handler->Close_fifo();
  fifo_handler->Delete_fifo();
  free(root_dir_name);
  kill(getppid(),SIGCHLD);
  exit(0);
}



//==CONSTRUCTOR-DESTRUCTOR===//

Receiver::Receiver(Error_Handler_Interface *handler,Fifo_pipe_handler* fifo_handler,Read_Write_handler* read_write_handler){
  this->handler = handler;
  this->fifo_handler = fifo_handler;
  this->read_write_handler = read_write_handler;

}

Receiver::~Receiver() {
  delete handler;
  delete read_write_handler;
  delete fifo_handler;
}

//==INNER-FUNCTIONALITY==//

bool Receiver::do_fork() {
  pid_t pid;
  if((pid=fork())==-1)
    handler->Terminating_Error("Fork failed");
  return pid;
}

char * Receiver::Create_dir_for_sender_in_mirror(const int &client_id, const char *mirror_dir_path_name) {

  //1.construct the dir name;
  char* new_dir_name = Construct_new_dir_path_name(client_id,mirror_dir_path_name);
  //2.make the dir
  if(mkdir(new_dir_name,0777)==-1){
    kill(getppid(),SIGUSR1);
    handler->Terminating_Error("Failed to make dir in mirror");
  }
  return new_dir_name;


}

char *Receiver::Construct_new_dir_path_name(const int &client_id, const char *mirror_dir_path_name) {

  char* new_dir_path_name;
  char client_id_buffer[20];
  sprintf(client_id_buffer,"%d",client_id);

  new_dir_path_name=String_Manager::Allocate(strlen(mirror_dir_path_name)+strlen(client_id_buffer)+2);
  sprintf(new_dir_path_name,"%s/%s",mirror_dir_path_name,client_id_buffer);
  return new_dir_path_name;

}

void Receiver::Get_input(const char *root_dir_name, Log_file_handler *log_file_handler) {

  bool input_done= false;
  fifo_handler->Set_to_Non_blocking();
  while (!input_done){
    char* filename = Read_filename();
    if(filename==NULL)
      return;

    char* file_full_path_name = Construct_full_file_path_name(filename,root_dir_name);
    u_int32_t file_size = Read_file_size();
    Read_from_pipe_and_write_in_file(file_full_path_name, file_size);
    log_file_handler->Log_Received_file(file_size);

    free(file_full_path_name);
    free(filename);
  }

}

char *Receiver::Read_filename() {

  u_int16_t filename_size;
  fifo_handler->Read_in_fifo_with_custom_buffer_size_with_timeout(sizeof(u_int16_t),&filename_size);

  if(filename_size==0)
    return NULL;

  char* filename = String_Manager::Allocate(filename_size+1);
  fifo_handler->Read_in_fifo_with_custom_buffer_size_with_timeout(filename_size,filename);
  return filename;


}

char *Receiver::Construct_full_file_path_name(char *filename, const char *full_path_name) {

  char* token;
  char* full_path_until_now = String_Manager::Allocate_and_copy(full_path_name);
  token=strtok(filename,"/");

  while (token!=NULL){
    full_path_until_now =(char*)realloc(full_path_until_now, sizeof(char)*(strlen(full_path_until_now)+strlen(token)+2));
    sprintf(full_path_until_now,"%s/%s",full_path_until_now,token);

    token = strtok(NULL,"/");
    if(token!=NULL)
      Check_if_dir_exists_and_create_if_needed(full_path_until_now);
  }
  Create_file_in_mirror(full_path_until_now);
  return full_path_until_now;
}

void Receiver::Read_from_pipe_and_write_in_file(const char *file_path_name, const u_int32_t &file_size) {

  int file_fd = open(file_path_name,O_CREAT|O_WRONLY);
  if(file_size==0)
    return;

  u_int32_t bytes_left_to_receive = file_size;
  int local_buffer_size =fifo_handler->Get_buffer_size();

  if(bytes_left_to_receive<local_buffer_size)
    local_buffer_size= file_size;

  char buffer[local_buffer_size];


  while(fifo_handler->Read_in_fifo_with_custom_buffer_size_with_timeout(local_buffer_size,buffer)){
    read_write_handler->Write_and_check(file_fd,buffer,local_buffer_size);
    bytes_left_to_receive=Calculate_bytes_left(bytes_left_to_receive,local_buffer_size);
    local_buffer_size=Calculate_new_local_buffer_size(bytes_left_to_receive,local_buffer_size);
  }
}

bool Receiver::Check_if_input_is_done() {

  u_int16_t flag;
  fifo_handler->Read_in_fifo_with_custom_buffer_size_with_timeout(sizeof(u_int16_t),&flag);

  if(!flag)
    return true;
  else
    return false;


}

u_int32_t Receiver::Calculate_bytes_left(const u_int32_t &bytes_left_to_receive, const int &local_buffer_size) {
  return bytes_left_to_receive-local_buffer_size;

}

int Receiver::Calculate_new_local_buffer_size(const u_int32_t &bytes_left_to_receice, const int &local_buffer_size) {

  if(bytes_left_to_receice<local_buffer_size)
    return bytes_left_to_receice;
  else
    return local_buffer_size;

}

u_int32_t Receiver::Read_file_size() {
  u_int32_t file_size;
  fifo_handler->Read_in_fifo_with_custom_buffer_size_with_timeout(sizeof(u_int32_t),&file_size);
  return file_size;
}

void Receiver::Check_if_dir_exists_and_create_if_needed(const char *full_path_until_now) {

  DIR* dir = opendir(full_path_until_now);
  if(dir!=NULL){
    closedir(dir);
  }

  else if(errno==ENOENT){
    mkdir(full_path_until_now,0777);
  }
}

void Receiver::Create_file_in_mirror(const char *full_path_name) {

  int fd;
  fd=open(full_path_name,O_CREAT,0777);
  close(fd);
}













