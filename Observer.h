#ifndef PROJ_2_OBSERVER_H
#define PROJ_2_OBSERVER_H
#include "Clients_List.h"

class Observable;


class Observer {
 public:
  virtual Clients_List * dir_changed(Observable &source, Clients_List &new_state)=0;
  virtual Clients_List *find_added_and_deleted(Clients_List &new_state) =0;
};

#endif //PROJ_2_OBSERVER_H
