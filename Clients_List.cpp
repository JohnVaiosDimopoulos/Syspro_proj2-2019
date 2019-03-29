#include "Clients_List.h"
#include "Factory.h"

//==CONSTRUCTOR-DESTRUCTOR==//
Clients_List::Clients_List(Error_Handler_Interface *handler) {
  this->head = NULL;
  this->handler = handler;
}

Clients_List::~Clients_List() {
  delete head;
  delete handler;
}

//==API==//


void Clients_List::Insert(int id) {

  Client_list_node* new_node = new Client_list_node(id);

  if(Is_Empty())
    Insert_In_Empty_list(new_node);
  else
    Insert_In_filled_list(new_node);

}

void Clients_List::Print() {

  Client_list_node* current = head;
  while (current!=NULL){
    std::cout<<current->getId()<<"->";
    current=current->getNext();
  }
  std::cout<<std::endl;

}


bool Clients_List::Delete(int id) {

  if(Is_Empty()){
    handler->Common_Eroor("The list is empty");
    return false;
  }
  if(Want_to_delete_first_element(id))
    return true;
  if(Want_to_delete_middle_element(id))
    return true;
  return false;
}

Client_list_node *Clients_List::Search(int id) {

  Client_list_node* current = head;

  while (current!=NULL){
    if(current->getId()==id)
      return current;
    current =current->getNext();
  }
  return NULL;

}

//===GETTERS-SETTERS==//




//==private==//

bool Clients_List::Is_Empty() {
  if(head==NULL)
    return true;
  return false;
}

void Clients_List::Insert_In_Empty_list(Client_list_node *new_node) {

  head = new_node;
}

void Clients_List::Insert_In_filled_list(Client_list_node *new_node) {

  new_node->setNext(head);
  head = new_node;
}

bool Clients_List::Want_to_delete_first_element(int id) {

  if(head->getId()==id){
    Client_list_node* temp_ptr = head;
    head = head->getNext();
    temp_ptr->setNext(NULL);
    delete temp_ptr;
  }
  return false;

}

bool Clients_List::Want_to_delete_middle_element(int id) {

  Client_list_node* current = head->getNext(),*previus = head;
  while (current!=NULL){

    if(current->getId()==id){
      previus->setNext(current->getNext());
      current->setNext(NULL);
      delete current;
      return true;
    }

    else{
      previus = current;
      current = current->getNext();
    }

  }
  return false;

}








