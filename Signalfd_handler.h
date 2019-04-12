#ifndef PROJ_2_SIGNALFD_HANDLER_H
#define PROJ_2_SIGNALFD_HANDLER_H

#include "Error_handler_interface.h"
#include "Signal_received.h"

class Signalfd_handler {
 private:
  int signal_fd;
  Error_Handler_Interface* handler;

  //==INNER-FUNCTIONALITY==//
  sigset_t set_up_signal_mask() const;
  void program_mask(sigset_t *mask) const;
  void init_signal_fd(sigset_t &mask);
  void Error_check(size_t res) const;




 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  Signalfd_handler(Error_Handler_Interface *handler);
  virtual ~Signalfd_handler();

  //==API==//
  void Init();
  Signal_received Get_next_signal();
  void Close_fd();

};

#endif //PROJ_2_SIGNALFD_HANDLER_H
