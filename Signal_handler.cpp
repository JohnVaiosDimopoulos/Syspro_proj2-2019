#include "Signal_handler.h"

#include <signal.h>
#include <sys/signalfd.h>
#include <iostream>
#include <unistd.h>

//===CONSTRUCTOR-DESTRUCTOR==//

Signal_handler::Signal_handler(Error_Handler_Interface *handler)
    : handler(handler){}

Signal_handler::~Signal_handler() {
  delete handler;
}


//==API==//
void Signal_handler::Init_signalfd() {
  sigset_t mask = set_up_signal_mask();
  program_mask(&mask);
  init_signal_fd(mask);
}

Signal_received Signal_handler::Get_next_signal() {

  struct signalfd_siginfo info;
  size_t res;

  // read signal from the fd and return the signum and the child pid that sended the signal
  res=read(signal_fd,&info, sizeof(info));
  Error_check(res);
  Signal_received sig(info.ssi_signo,info.ssi_pid);
  return sig;
}

void Signal_handler::Close_fd() {
  close(signal_fd);
}



//==INNER-FUNCTIONALITY==//
void Signal_handler::init_signal_fd(sigset_t &mask) {

  signal_fd = signalfd(-1, &mask, 0);
  if (signal_fd < 0)
    handler->Terminating_Error("error at opening the signal fd");
}

void Signal_handler::program_mask(sigset_t *mask) const {

  if ( sigprocmask(SIG_BLOCK, mask, NULL) < 0)
    handler->Terminating_Error("failed to prog mask");
}

sigset_t Signal_handler::set_up_signal_mask() const {
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  return mask;
}


void Signal_handler::Error_check(size_t res) const {
  if (res < 0)
    handler->Terminating_Error("Read error at signal_handler");

  if (res != sizeof(struct signalfd_siginfo))
    handler->Terminating_Error("Read error at signal handler");
}


