#include "Read_Write_handler.h"
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>

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

bool Read_Write_handler::Read_and_check_with_timeout(const int &file_desc, void *buffer, const size_t &size) {
  fd_set set;
  timeval tv;
  Set_up_fd_set(file_desc, set, tv);

  // we wait 30 sec until there is inptup
  int ret_val = select(file_desc+1,&set,NULL,NULL,&tv);

  if(ret_val==-1){
    // no input within 30sec
    kill(getppid(),SIGUSR1);
    handler->Terminating_Error("Select failed");
  }
  else if(ret_val){
    return Read_and_check_no_timeout(file_desc,buffer,size);
  }
  else{
    //other error
    kill(getppid(),SIGUSR1);
    handler->Terminating_Error("READER TIMEOUT");
  }


}

void Read_Write_handler::Set_up_fd_set(const int &file_desc, fd_set &set, timeval &tv) const {
  FD_ZERO(&set);
  FD_SET(file_desc, &set);
  tv.tv_sec = 30;
  tv.tv_usec = 0;
}


