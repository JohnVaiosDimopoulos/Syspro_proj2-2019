#ifndef PROJ_2_RECEIVER_H
#define PROJ_2_RECEIVER_H
#include "Error_handler_interface.h"
#include "Argument_data.h"
#include "Fifo_pipe_handler.h"
#include "Read_Write_handler.h"

class Receiver {
 private:
  Error_Handler_Interface* handler;
  Fifo_pipe_handler fifo_handler;
  Read_Write_handler read_write_handler;

  //==INNER-FUNCTIONALITY==//
  char * Create_dir_for_sender_in_mirror(const int &client_id, const char *mirror_dir_path_name);
  char* Construct_new_dir_path_name(const int& client_id,const char* mirror_dir_path_name);


 public:
  //==API==//
  void Receive_data(const int &client_id, const Argument_data &data);

  //==CONSTRUCTOR-DESTRUCTOR==//
  Receiver(Error_Handler_Interface *handler,Fifo_pipe_handler fifo_handler,Read_Write_handler read_write_handler);
  virtual ~Receiver();

};

#endif //PROJ_2_RECEIVER_H
