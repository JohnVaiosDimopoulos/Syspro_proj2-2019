#ifndef PROJ_2_STATUS_RECORD_H
#define PROJ_2_STATUS_RECORD_H

#include "child_status.h"
#include "Error_handler_interface.h"

class Status_Record {

 private:
  Error_Handler_Interface* handler;
  child_status* senders;
  child_status* receivers;
  int array_size;
  int next_sender_pos;
  int next_receiver_pos;

  //==INNER-FUNCTIONALITY==//
  int Serch_in_Senders(const int &child_id);
  int Search_in_Receivers(const int &child_id);

 public:
  //==CONSTRUCTOR-DESTRUCTOR==//
  Status_Record(Error_Handler_Interface *handler);
  virtual ~Status_Record();

  //==API==//
  void Allocate_arrays(const int& clients_num);
  void Insert_sender(const int& child_id, const int& client_id );
  void Insert_receiver(const int& child_id,const int& client_id);
  bool Check_if_done();
  bool Search_for_child_id_in_senders_and_receivers(const int &child_id, int *index);
  int get_clinet_from_sender(int index);
  int get_clinet_from_receiver(int index);
  void update_sender(int index, int new_child_id);
  void update_receiver(int index, int new_child_id);
  bool can_retry_sender(int index);
  bool can_retry_receiver(int index);
  void Set_sender_to_finished(int index);
  void Set_receiver_to_finished(int index);


};

#endif //PROJ_2_STATUS_RECORD_H
