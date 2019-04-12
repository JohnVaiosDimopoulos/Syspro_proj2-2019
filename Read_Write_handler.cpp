#include "Read_Write_handler.h"
#include <unistd.h>
#include <signal.h>

//==CONSTRUCTOR-DESTRUCTOR==//

Read_Write_handler::Read_Write_handler(Error_Handler_Interface *handler){
  this->handler = handler;
}

Read_Write_handler::~Read_Write_handler() {
  delete handler;
}

//==API==//

int Read_Write_handler::Write_and_check(const int &file_desc, const void *buffer, const size_t &size) {

  if(write(file_desc,buffer,size)==-1){
    kill(getppid(),SIGUSR1);
    handler->Terminating_Error("write failed");
  }
}

bool Read_Write_handler::Read_and_check_no_timeout(const int &file_desc, void *buffer, const size_t &size) {

  size_t ret_value;
  if((ret_value=read(file_desc,buffer,size))>0)
    return true;

  if(ret_value==-1){
    kill(getppid(),SIGUSR1);
    handler->Terminating_Error("Read failed");
  }

}

bool Read_Write_handler::Read_and_check_with_timeout(const int &fle_desc, void *buffer, const size_t &size) {

  int sec_waited=0;
  size_t read_ret_value;

  while (1){

    if(sec_waited>30){
      kill(getppid(),SIGUSR2);
      handler->Terminating_Error("proccess timed out");
    }

    read_ret_value = read(fle_desc,buffer,size);

    if(read_ret_value<0){
      if(read_ret_value==-1 && errno==EAGAIN){
      sec_waited++;
      continue;
      }
      else{
        kill(getppid(),SIGUSR1);
        handler->Terminating_Error("read with timeout failed");
      }
    }
    else
      return read_ret_value;
  }

}


