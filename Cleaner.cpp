#include "Cleaner.h"
#include "Argument_data.h"
#include "String_Manager.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <unistd.h>

//===CONSTRUCTOR-DESTRUCTOR==//
Cleaner::Cleaner(Error_Handler_Interface *handler) {
  this->handler = handler;
}

Cleaner::~Cleaner() {
  delete handler;
}


//==API==//
void Cleaner::clean(const Argument_data &data) {

  //1.delete id_file;
  Delete_from_common(data.getCommon_dir_name(), data.getId());
  //2. delete_mirror_recursively
  Delete_dir(data.getMirror_dir_name());

}
//==INNER-FUNCTIONALITY==//

void Cleaner::Delete_from_common(const char *common_file_name, const int id) {

  char file_path[200];
  sprintf(file_path,"%s/%d.id",common_file_name,id);
  if(remove(file_path)!=0)
    handler->Terminating_Error("Error deleting id file");
}

void Cleaner::Delete_dir(const char *current_dir_name) {
  //TODO:MAKE A RECURSIVE FUNCTION THAT DELETES MIRROR
  DIR*  current_dir;
  struct dirent* dir_ptr;
  struct stat stat_buf;

  if((current_dir=opendir(current_dir_name))==NULL)
    handler->Terminating_Error("failed to open dir durring mirror dir deletion");

  while((dir_ptr=readdir(current_dir))!=NULL){

    if(dir_ptr->d_name[0]=='.')
      continue;

    char* newpath = String_Manager::Allocate((strlen(current_dir_name)+strlen(dir_ptr->d_name)+2));
    sprintf(newpath,"%s/%s",current_dir_name,dir_ptr->d_name);

    if((stat(newpath,&stat_buf))==-1)
      handler->Terminating_Error("Stat failed");

    if((stat_buf.st_mode & S_IFMT)==S_IFDIR){
      Delete_dir(newpath);
    } else
      remove(newpath);
    free(newpath);
  }
  rmdir(current_dir_name);
}




