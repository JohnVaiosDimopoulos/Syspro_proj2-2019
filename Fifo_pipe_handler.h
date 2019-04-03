#ifndef PROJ_2_FIFO_PIPE_HANDLER_H
#define PROJ_2_FIFO_PIPE_HANDLER_H

#include "Error_handler_interface.h"
class Argument_data;


class Fifo_pipe_handler {
 private:
  Error_Handler_Interface* handler;

  //==INNER-FUNCTIONALITY==//
  void Make_fifo(const char* fifo_name);
  char* Construct_fifo_name(const int& receiver_id,const Argument_data& data);
  int Calculate_pipe_path_size(const int &receiver_id, const Argument_data &data);
  int Open_fifo_from_name(const char *fifo_name);




 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  Fifo_pipe_handler(Error_Handler_Interface *handler);

  //==API==//
  int Make_and_open_fifo(const int &receiver_id, const Argument_data &data);
  int Open_fifo(const int& client_id,const Argument_data& data);


};

#endif //PROJ_2_FIFO_PIPE_HANDLER_H
