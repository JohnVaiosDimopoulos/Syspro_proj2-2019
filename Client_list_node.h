#ifndef PROJ_2_CLIENT_LIST_NODE_H
#define PROJ_2_CLIENT_LIST_NODE_H
#include <iostream>

class Client_list_node {
 private:
  const int id;
  Client_list_node* next;

 public:
  Client_list_node(int id):id(id){
    this->next = NULL;
  }
  ~Client_list_node(){
      delete next;
  }

  Client_list_node *getNext() const {
    return next;
  }
  void setNext(Client_list_node *next) {
    Client_list_node::next = next;
  }

  const int getId() const {
    return id;
  }
};

#endif //PROJ_2_CLIENT_LIST_NODE_H
