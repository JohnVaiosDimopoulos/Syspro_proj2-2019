#ifndef PROJ_2_FIFO_PIPE_HANDLER_H
#define PROJ_2_FIFO_PIPE_HANDLER_H

#include <sys/stat.h>
#include "Error_handler_interface.h"
#include "Read_Write_handler.h"

class Argument_data;


class Fifo_pipe_handler {
 private:
  Error_Handler_Interface* error_handler;
  Read_Write_handler* read_write_handler;
  char* fifo_path_name;
  int fifo_fd;
  int buffer_size;


  //==INNER-FUNCTIONALITY==//
  void Make_fifo(const char* fifo_name);
  char* Construct_fifo_name_for_sender(const int &receiver_id, const Argument_data &data);
  int Calculate_pipe_path_size(const int &receiver_id, const Argument_data &data);
  int Get_fifo_fd_for_sender(const char *fifo_name);
  char* Construct_fifo_name_for_receiver(const int& sender_id,const Argument_data& data);
  int Get_fifo_fd_for_receiver(const char *fifo_name);




 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  Fifo_pipe_handler(Error_Handler_Interface *handler,Read_Write_handler* read_write_handler);

  virtual ~Fifo_pipe_handler();



  //==API==//
  void Make_and_open_fifo(const int &receiver_id, const Argument_data &data);
  void Open_fifo_at_receiver_non_blocking(const int &client_id, const Argument_data &data);
  void Close_fifo();
  void Delete_fifo();
  int Get_buffer_size();


  void Write_in_fifo_with_custom_buffer_size(size_t buffer_size, const void *buffer);
  bool Read_in_fifo_with_custom_buffer_size_with_timeout(size_t buffer_size, void *buffer);

};

#endif //PROJ_2_FIFO_PIPE_HANDLER_H
