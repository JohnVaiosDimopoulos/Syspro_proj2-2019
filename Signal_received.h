#ifndef PROJ_2_SIGNAL_RECEIVED_H
#define PROJ_2_SIGNAL_RECEIVED_H

#include <sys/types.h>

class Signal_received {
 private:
  const u_int32_t signal;
  const u_int32_t pid;
 public:
  Signal_received(u_int32_t signal, u_int32_t pid) : signal(signal), pid(pid) {}

  u_int32_t Get_Signal(){ return signal;}
  u_int32_t Get_Pid(){ return pid;}
};

#endif //PROJ_2_SIGNAL_RECEIVED_H
