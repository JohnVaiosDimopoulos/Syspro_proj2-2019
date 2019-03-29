#ifndef PROJ_2_CLIENTS_LIST_H
#define PROJ_2_CLIENTS_LIST_H
#include "Client_list_node.h"
#include "Error_handler_interface.h"

class Clients_List {

 private:
  Client_list_node* head;
  Error_Handler_Interface* handler;
  bool Is_Empty();
  void Insert_In_Empty_list(Client_list_node *new_node);
  void Insert_In_filled_list(Client_list_node *new_node);
  bool Want_to_delete_first_element(int id);
  bool Want_to_delete_middle_element(int id);

 public:
  //==constructor-destructor==//
  Clients_List(Error_Handler_Interface *handler);
  ~Clients_List();
  //==API==//
  void Insert(int id);
  bool Delete(int id);
  Client_list_node* Search(int id);
  void Print();


};

#endif //PROJ_2_CLIENTS_LIST_H
