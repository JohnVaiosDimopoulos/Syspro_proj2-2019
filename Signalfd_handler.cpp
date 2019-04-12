#include "Signalfd_handler.h"

#include <signal.h>
#include <sys/signalfd.h>
#include <iostream>
#include <unistd.h>

//===CONSTRUCTOR-DESTRUCTOR==//

Signalfd_handler::Signalfd_handler(Error_Handler_Interface *handler)
    : handler(handler){}

Signalfd_handler::~Signalfd_handler() {
  delete handler;
}


//==API==//
void Signalfd_handler::Init() {
  sigset_t mask = set_up_signal_mask();
  program_mask(&mask);
  init_signal_fd(mask);
}

Signal_received Signalfd_handler::Get_next_signal() {

  struct signalfd_siginfo info;
  size_t res;

  res=read(signal_fd,&info, sizeof(info));
  Error_check(res);
  return Signal_received(info.ssi_signo,info.ssi_pid);
}

void Signalfd_handler::Close_fd() {
  close(signal_fd);
}



//==INNER-FUNCTIONALITY==//
void Signalfd_handler::init_signal_fd(sigset_t &mask) {

  signal_fd = signalfd(-1, &mask, 0);
  if (signal_fd < 0)
    handler->Terminating_Error("error at opening the signal fd");
}

void Signalfd_handler::program_mask(sigset_t *mask) const {

  if ( sigprocmask(SIG_BLOCK, mask, NULL) < 0)
    handler->Terminating_Error("failed to prog mask");
}

sigset_t Signalfd_handler::set_up_signal_mask() const {
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  sigaddset(&mask, SIGUSR2);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGQUIT);
  return mask;
}


void Signalfd_handler::Error_check(size_t res) const {
  if (res < 0)
    handler->Terminating_Error("Read error at signal_handler");

  if (res != sizeof(struct signalfd_siginfo))
    handler->Terminating_Error("Read error at signal handler");
}

