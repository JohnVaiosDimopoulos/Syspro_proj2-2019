#ifndef PROJ_2_CHILD_STATUS_H
#define PROJ_2_CHILD_STATUS_H

#include <unistd.h>
enum  status {PENDING,SUCCESS,FAILED};

class child_status {

 private:
  status current_status;
  pid_t child_id;
  // the client that this child is sending or receiving
  int client_id;
  int num_of_retries;
 public:

  //==CONSTRUCTOR==//
  child_status() : child_id(0), client_id(0), current_status(PENDING), num_of_retries(0){}

  //==GETTERS==//
  status Get_status() const { return current_status;}
  pid_t get_child_id() const {return child_id;}
  int get_client_id() const {return client_id;}
  int get_num_of_retries() const {return num_of_retries;}

  //==SETTERS==//
  void set_current_status_to_SUCCESS() {current_status = SUCCESS;}
  void set_current_status_to_FAILED() {current_status = FAILED;}
  void set_child_id(pid_t childId) {child_id = childId;}
  void set_client_id(int clientId){client_id = clientId;}
  void new_retry() {num_of_retries++;}

};

#endif //PROJ_2_CHILD_STATUS_H
