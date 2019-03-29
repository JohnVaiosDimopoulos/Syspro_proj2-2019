#include "common_dir_Observer.h"
#include "Factory.h"



//==CONSTRUCTOR==//
common_dir_Observer::common_dir_Observer(int& client_id,Clients_List& list) : old_state(list) {
  old_state.Insert(client_id);
}


//==API==//
Clients_List * common_dir_Observer::dir_changed(Observable &source, Clients_List &new_state) {
  Clients_List* arr = (Clients_List*)malloc(sizeof(Clients_List)*2);

  for(int i =0;i<2;i++)
    arr[i] = Factory::Create_List();

  arr[1] = find_added(new_state);
  arr[2] = find_deleted(new_state);
  return arr;
}




//==INNER-FUNCTIONALITY==//

Clients_List common_dir_Observer::find_added(Clients_List& new_state) {
  //create list
  // run the new_state
  // for each item that is not in old we insert it into the list we insert it into the list we retunr


}


Clients_List common_dir_Observer::find_deleted(Clients_List& new_state) {
  // create a new list
  // for each item in old check if it exists in the new
  // each item that doestnt is added in the list that we return
}







