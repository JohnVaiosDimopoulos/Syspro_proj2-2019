#include "Read_Write_handler.h"
#include <unistd.h>

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
    handler->Common_Eroor("Write in sender failed");
    //send signal
    //TODO signal here
    exit(-1);
  }
}

bool Read_Write_handler::Read_and_check_no_timeout(const int &file_desc, void *buffer, const size_t &size) {

  size_t ret_value;
  if((ret_value=read(file_desc,buffer,size))>0)
    return true;

  if(ret_value==-1){
    handler->Common_Eroor("READ ERROR");
    //TODO signal here
    //send_signal;
  }

}

bool Read_Write_handler::Read_and_check_with_timeout(const int &fle_desc, void *buffer, const size_t &size) {

  int sec_waited=0;
  size_t read_ret_value;

  while (1){

    if(sec_waited>30){
      //TODO:send timeout_signal
      std::cout<<"timeout"<<std::endl;
      exit(-1);
    }

    read_ret_value = read(fle_desc,buffer,size);

    if(read_ret_value<0){
      if(read_ret_value==-1 && errno==EAGAIN){
      sec_waited++;
      continue;
      }
      else{
        handler->Terminating_Error("ERROR IN READ");
        exit(-1);
        //TODO send signal;
      }
    }
    else
      return read_ret_value;
  }

}


