#ifndef PROJ_2_RECEIVER_H
#define PROJ_2_RECEIVER_H
#include "Error_handler_interface.h"
#include "Argument_data.h"
#include "Fifo_pipe_handler.h"
#include "Read_Write_handler.h"
#include "Log_file_handler.h"

class Receiver {
 private:
  Error_Handler_Interface* handler;
  Fifo_pipe_handler* fifo_handler;
  Read_Write_handler* read_write_handler;


  //==INNER-FUNCTIONALITY==//
  int do_fork();
  void Get_input(const char *root_dir_name, Log_file_handler *log_file_handler);
  char * Create_dir_for_sender_in_mirror(const int &client_id, const char *mirror_dir_path_name);
  char* Construct_new_dir_path_name(const int& client_id,const char* mirror_dir_path_name);
  char *Read_filename();
  char *Construct_full_file_path_name(char *filename, const char *full_path_name);
  void Read_from_pipe_and_write_in_file(const char *file_path_name, const u_int32_t &file_size);
  u_int32_t Read_file_size();
  void Check_if_dir_exists_and_create_if_needed(const char *full_path_until_now);
  void Create_file_in_mirror(const char* full_path_name);
  bool Check_if_input_is_done();
  u_int32_t Calculate_bytes_left(const u_int32_t&  bytes_left_to_receive,const int& local_buffer_size);
  int Calculate_new_local_buffer_size(const u_int32_t& bytes_left_to_receice,const int& local_buffer_size);


 public:
  //==API==//
  int Receive_data(const int &client_id, const Argument_data &data, Log_file_handler log_file_handler);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Receiver(Error_Handler_Interface *handler,Fifo_pipe_handler* fifo_handler,Read_Write_handler* read_write_handler);
  virtual ~Receiver();

};

#endif //PROJ_2_RECEIVER_H
