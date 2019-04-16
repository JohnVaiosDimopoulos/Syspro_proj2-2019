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

Clients_List::Clients_List(const Clients_List &src) {
  head =NULL;
  this->handler = Factory::Create_Error_Handler();
  Client_list_node* curr = src.getHead();
  while (curr!=NULL){
    Insert(curr->getId());
    curr = curr->getNext();
  }
}

//==API==//


void Clients_List::Insert(int id) {

  //insert element on top

  Client_list_node* new_node = new Client_list_node(id);

  if(Is_Empty())
    Insert_In_Empty_list(new_node);
  else
    Insert_In_filled_list(new_node);

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

void Clients_List::swap_heads(Clients_List& src) {
  Client_list_node* temp;
  temp=src.getHead();
  src.setHead(NULL);
  this->head=temp;
}


//==OPERATORS==//

Clients_List &Clients_List::operator=(Clients_List src){
  if(src.getHead()!=NULL)
    swap_heads(src);
  return *this;
}




//==GETTERS-SETTERS==//

Client_list_node *Clients_List::getHead() const {
  return head;
}

void Clients_List::setHead(Client_list_node *head) {
  Clients_List::head = head;
}

int Clients_List::Get_length() {
  int lenght=0;

  for(Client_list_node* current = head;current!=NULL;current=current->getNext())
    lenght++;

  return lenght;
}








