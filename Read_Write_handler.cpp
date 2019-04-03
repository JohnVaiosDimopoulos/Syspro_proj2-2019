#include "Read_Write_handler.h"
#include <unistd.h>

//==CONSTRUCTOR-DESTRUCTOR==//

Read_Write_handler::Read_Write_handler(Error_Handler_Interface *handler) : handler(handler) {}

Read_Write_handler::~Read_Write_handler() {
  delete handler;
}

//==API==//

int Read_Write_handler::Write_and_check(const int &file_desc, const void *buffer, const size_t &size) {

  if(write(file_desc,buffer,size)==-1){
    handler->Common_Eroor("Write in sender failed");
    //send signal
    exit(-1);
  }
}

bool Read_Write_handler::Read_and_check(const int &file_desc, void *buffer, const size_t &size) {

  size_t ret_value;
  if((ret_value=read(file_desc,buffer,size))>0)
    return true;

  if(ret_value==-1){
    handler->Common_Eroor("READ ERROR");
    //send_signal;
  }

}


