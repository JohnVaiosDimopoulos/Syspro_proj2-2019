#include "Status_Record.h"
#include <cstdlib>


//==CONSTRUCTOR-DESTRUCTOR==//
Status_Record::Status_Record(Error_Handler_Interface *handler) : handler(handler),receivers(NULL),senders(NULL),next_receiver_pos(0),next_sender_pos(0),array_size(0){}

Status_Record::~Status_Record() {
  delete handler;
  delete[] senders;
  delete[] receivers;

}


//==API==//
void Status_Record::Allocate_arrays(const int &clients_num) {
  senders = new child_status[clients_num];
  receivers = new child_status[clients_num];
  array_size = clients_num;
}

void Status_Record::Insert_sender(const int &child_id, const int &client_id) {
  senders[next_sender_pos].set_child_id(child_id);
  senders[next_sender_pos].set_client_id(client_id);
  next_sender_pos++;
}

void Status_Record::Insert_receiver(const int &child_id, const int &client_id) {
  receivers[next_receiver_pos].set_client_id(client_id);
  receivers[next_receiver_pos].set_child_id(child_id);
  next_receiver_pos++;

}


int Status_Record::get_clinet_from_sender(int index) {
  return senders[index].get_client_id();

}

int Status_Record::get_clinet_from_receiver(int index) {
  return receivers[index].get_client_id();
}


void Status_Record::update_sender(int index, int new_child_id) {
  senders[index].set_child_id(new_child_id);
  senders[index].new_retry();
}

void Status_Record::update_receiver(int index, int new_child_id) {
  receivers[index].set_child_id(new_child_id);
  receivers[index].new_retry();

}

void Status_Record::Set_sender_to_finished(int index) {
  senders[index].set_current_status_to_SUCCESS();
}

void Status_Record::Set_receiver_to_finished(int index) {
  receivers[index].set_current_status_to_SUCCESS();
}


bool Status_Record::Check_if_done() {

  // if no element from senders nor receivers has a PENDING status we return
  for(int i =0;i<array_size;i++){
    if(senders[i].Get_status()==PENDING || receivers[i].Get_status()==PENDING){
      return false;
    }
  }
  return true;

}

bool Status_Record::can_retry_sender(int index) {
  // check if the retries are 3
  // if they are set status to FAILED
  if(senders[index].get_num_of_retries()>=3){
    senders[index].set_current_status_to_FAILED();
    return false;
  }
  return true;
}

bool Status_Record::can_retry_receiver(int index) {
  if(receivers[index].get_num_of_retries()>=3){
    receivers[index].set_current_status_to_FAILED();
    return false;
  }

  return true;
}


//==INNER-FUNCTIONALITY==//
int Status_Record::Serch_in_Senders(const int &child_id) {
  for(int i =0;i<array_size;i++){
    if(senders[i].get_child_id()==child_id)
      return i;
  }

  return -1;
}

int Status_Record::Search_in_Receivers(const int &child_id) {
  for(int i =0;i<array_size;i++){
    if(receivers[i].get_child_id()==child_id)
      return i;
  }

  return -1;
}

bool Status_Record::Search_for_child_id_in_senders_and_receivers(const int &child_id, int *index) {
  int res;
  // if the child is in senders return false and put its possition in the array in index
 if((res=Search_in_Receivers(child_id))!=-1){
   *index = res;
   return false;}

  // if the child is in receivers return true and put its possition in the array in index
  if(((*index)=Serch_in_Senders(child_id))!=-1)
   return true;


}









