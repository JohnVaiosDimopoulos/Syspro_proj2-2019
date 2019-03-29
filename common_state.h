#ifndef PROJ_2_COMMON_STATE_H
#define PROJ_2_COMMON_STATE_H
#include "Observable.h"

class common_state: public Observable {
 private:
  Clients_List get_common_state(const char *common_dir_name);
 public:
  Clients_List * update(const char *common_dir_name) override;
};


#endif //PROJ_2_COMMON_STATE_H
