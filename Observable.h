#ifndef PROJ_2_OBSERVABLE_H
#define PROJ_2_OBSERVABLE_H
#include "Observer.h"


class Observable{
 private:
  Observer* observer;
 protected:
  Clients_List* notify(Observable& source,Clients_List& new_state){
    observer->dir_changed(source,new_state);
  }

 public:
  void set_observer(Observer& observer) {
    this->observer = &observer;
  }

  virtual Clients_List * update(const char *) =0;

};

#endif //PROJ_2_OBSERVABLE_H
