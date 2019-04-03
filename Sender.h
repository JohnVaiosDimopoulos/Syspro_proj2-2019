#ifndef PROJ_2_SENDER_H
#define PROJ_2_SENDER_H
#include <sys/types.h>
#include "Error_handler_interface.h"
#include "Argument_data.h"
#include "Fifo_pipe_handler.h"
#include "Read_Write_handler.h"

#include <dirent.h>

class Sender {
 private:
  Error_Handler_Interface* handler;
  Fifo_pipe_handler fifo_handler;
  Read_Write_handler read_write_handler;


  //==INNER-FUNCTIONALITY==//
  pid_t do_fork();
  DIR * Open_dir(const char *input_dir_name);
  void Recursively_go_Through_dir_and_send(const char *current_path_relative_to_input_dir,const char *current_dir_full_path,const int &fifo_pipe_fd,const int &pipe_buffer);
  char * create_path_name_relative_to_input(const char *path_relative_to_input_dir, char *file_name);
  char * create_full_path_name(const char *current_dir_name, const char *file_name);
  void Check_and_stat(struct stat *stat_buf,const char* full_path_name);
  void Deallocate_strings(char *full_path_name, char *path_name_relative_to_input) const;
  bool Is_file(struct stat* stat_buf);
  bool Is_Dir(struct stat* stat_buf);
  void Send_through_pipe(const char* full_file_path, const char* file_path_relative_to_input,const int& fifo_pipe_fd,const int& pipe_buffer);
  size_t Read_from_file_and_write_in_pipe(const int &fifo_pipe_fd,const int &fifo_buffer_size,const int &input_file_fd,const u_int32_t &file_size);
  void Mark_end_of_input(const int& fifo_pipe_fd);
  u_int32_t Caluculate_bytes_left_to_send(const u_int32_t &bytes_left_to_send, int *buffer_size);


 public:

  //==API==//
  void Send_data(const int &client_id, const Argument_data &data);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Sender(Error_Handler_Interface *handler, Fifo_pipe_handler fifo_handler,Read_Write_handler read_write_handler);
  virtual ~Sender();


};

#endif //PROJ_2_SENDER_H
