#ifndef PROJ_2_SIGNAL_HANDLER_H
#define PROJ_2_SIGNAL_HANDLER_H

#include "Error_handler_interface.h"
#include "Signal_received.h"
#include "Cleaner.h"
#include "Argument_data.h"

class Signal_handler {
 private:
  int signal_fd;
  Error_Handler_Interface* handler;


  //==INNER-FUNCTIONALITY==//
  sigset_t set_up_signal_mask() const;
  void program_mask(sigset_t *mask) const;
  void init_signal_fd(sigset_t &mask);
  void Error_check(size_t res) const;
  static void Exit_handler(int signum);




 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  Signal_handler(Error_Handler_Interface *handler);
  virtual ~Signal_handler();

  //==API==//
  void Init_signalfd();
  Signal_received Get_next_signal();
  void Close_fd();

};

#endif //PROJ_2_SIGNAL_HANDLER_H
