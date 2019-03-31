#ifndef PROJ_2_COMMON_STATE_H
#define PROJ_2_COMMON_STATE_H
#include <dirent.h>
#include <sys/stat.h>
#include "Error_Handler.h"
#include "Clients_List.h"


class common_dir_monitor{

 private:
  //==Members==//
  Clients_List old_dir_state;
  Error_Handler_Interface* handler;

  //==inner-functionallity==//
  int Tokenize_id_file_name(char *id_file_name) const;
  DIR *Check_and_open_dir(const char *common_dir_name) const;
  char *get_file_path_name(const char *common_dir_name,const char* id_file_name) const;
  void Check_and_get_stat(struct stat* stat_buf,char* file_path_name);
  Clients_List * get_common_state(const char *common_dir_name, int my_id);
  Clients_List * find_added(Clients_List &new_state);
  Clients_List * find_deleted(Clients_List &new_state);
  Clients_List **Allocate_array_to_return() const;
  void update_old_state(Clients_List& new_state);


 public:
  //==API==//
  Clients_List** update(const char *common_dir_name, int my_id);
  //==CONST-DEST==//
  common_dir_monitor(Error_Handler_Interface* handler,Clients_List list);
  virtual ~common_dir_monitor();

};


#endif //PROJ_2_COMMON_STATE_H
