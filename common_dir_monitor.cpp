#include "common_dir_monitor.h"
#include "String_Manager.h"
#include "Factory.h"

//==INNER-FUNCTIONALITY==//
Clients_List * common_dir_monitor::get_common_state(const char *common_dir_name, int my_id) {

  Clients_List* list = new Clients_List(Factory::Create_Error_Handler());
  DIR* current_directory = Check_and_open_dir(common_dir_name);
  struct dirent* dir_ptr;

  while ((dir_ptr=readdir(current_directory))!=NULL){
    //ignore hidden files
    if(dir_ptr->d_name[0]=='.')
      continue;

    struct stat stat_buf;
    char *file_path_name = get_file_path_name(common_dir_name, dir_ptr->d_name);
    Check_and_get_stat(&stat_buf,file_path_name);
    if((stat_buf.st_mode &S_IFMT)==S_IFREG){
      int id = Tokenize_id_file_name(dir_ptr->d_name);
      // we dont put our own id_file in the list
      if(id==my_id)
        continue;
      list->Insert(id);
    }
  }
  closedir(current_directory);

  return list;

}

char *common_dir_monitor::get_file_path_name(const char *common_dir_name, const char* id_file_name) const {
  char *file_path_name = String_Manager::Allocate(strlen(common_dir_name) + strlen(id_file_name) + 2);
  sprintf(file_path_name, "%s/%s", common_dir_name, id_file_name);
  return file_path_name;
}

DIR *common_dir_monitor::Check_and_open_dir(const char *common_dir_name) const {

  DIR *current_directory;
  if ((current_directory = opendir(common_dir_name)) == NULL)
    handler->Terminating_Error("Cannot open current_directory");
  return current_directory;
}

int common_dir_monitor::Tokenize_id_file_name(char *id_file_name) const {
  char buffer[25];
  char *token;
  token = strtok(id_file_name, ".");
  int id = atoi(token);
  return id;
}

void common_dir_monitor::Check_and_get_stat(struct stat* stat_buf,char* file_path_name) {

  if(stat(file_path_name,stat_buf)==-1)
    handler->Terminating_Error("failed to get file status");
  free(file_path_name);

}

Clients_List * common_dir_monitor::find_added(Clients_List &new_state) {

  Clients_List* added = Factory::Create_List_in_heap();
  for(Client_list_node* current = new_state.getHead();current!=NULL;current=current->getNext()){
    if(old_dir_state.Search(current->getId())==NULL){
      added->Insert(current->getId());
    }
  }
  return added;
}

Clients_List * common_dir_monitor::find_deleted(Clients_List &new_state){

  Clients_List* deleted = Factory::Create_List_in_heap();
  for(Client_list_node* current = old_dir_state.getHead();current!=NULL;current=current->getNext()){
    if(new_state.Search(current->getId())==NULL){
      deleted->Insert(current->getId());
    }
  }
  return deleted;


}

Clients_List **common_dir_monitor::Allocate_array_to_return() const {

  Clients_List **array_to_return = new Clients_List*[2];
  for (int i = 0; i < 2; i++)
    array_to_return[i] = Factory::Create_List_in_heap();
  return array_to_return;
}

void common_dir_monitor::update_old_state(Clients_List &new_state) {

  old_dir_state=new_state;

}


//==API==//
Clients_List** common_dir_monitor::update(const char *common_dir_name, int my_id) {

  Clients_List* new_state = get_common_state(common_dir_name,my_id);
  Clients_List** array_to_return = Allocate_array_to_return();
  array_to_return[0]=find_added(*new_state);
  array_to_return[1]=find_deleted(*new_state);
  update_old_state(*new_state);
  delete new_state;
  return array_to_return;
}




//==CONSTRUCTOR-DESTRUCTOR==//
common_dir_monitor::~common_dir_monitor() {
  delete handler;
}

common_dir_monitor::common_dir_monitor(Error_Handler_Interface *handler,Clients_List list):old_dir_state(list) {
  this->handler=handler;
}




