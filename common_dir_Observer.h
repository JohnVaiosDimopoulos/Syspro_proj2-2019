#ifndef PROJ_2_COMMON_DIR_OBSERVER_H
#define PROJ_2_COMMON_DIR_OBSERVER_H
#include "Observer.h"

class common_dir_Observer: public Observer {
 private:
  Clients_List old_state;
  Clients_List find_added(Clients_List& new_state);
  Clients_List find_deleted(Clients_List& new_state);
 public:

  common_dir_Observer(int& client_id,Clients_List& list);
  Clients_List * dir_changed(Observable &source, Clients_List &new_state) override;

};

#endif //PROJ_2_COMMON_DIR_OBSERVER_H
