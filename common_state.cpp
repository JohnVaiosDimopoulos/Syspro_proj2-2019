#include "common_state.h"

//==INNER-FUNCTIONALITY==//
Clients_List common_state::get_common_state(const char *common_dir_name) {
  // open the dir
  // for each file add an item in the list
}

//==API==//
Clients_List * common_state::update(const char *common_dir_name) {

  Clients_List list = get_common_state(common_dir_name);
  return notify(*this,list);
}

