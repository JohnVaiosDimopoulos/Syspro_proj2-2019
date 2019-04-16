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
void Cleaner::clean(char *mirror_dir_name, char *common_dir_name) {

  //1.delete id_file;
  Delete_from_common(common_dir_name);
  //2. delete_mirror_recursively
  Delete_dir(mirror_dir_name);

}


void Cleaner::Delete_from_common(const char *common_file_name) {

  //removes the clients .id file from common
  if(remove(common_file_name)!=0)
    handler->Terminating_Error("Error deleting id file");
}

void Cleaner::Delete_dir(const char *current_dir_name) {
  // recursively deletes a dir
  DIR*  current_dir;
  struct dirent* dir_ptr;
  struct stat stat_buf;

  // check if dir exists and open it
  if((current_dir=opendir(current_dir_name))==NULL)
    handler->Terminating_Error("failed to open dir durring mirror dir deletion");

  // start reading from dir
  while((dir_ptr=readdir(current_dir))!=NULL){

    //ignore hidden files
    if(dir_ptr->d_name[0]=='.')
      continue;

    // get the path of current file
    char* newpath = String_Manager::Allocate((strlen(current_dir_name)+strlen(dir_ptr->d_name)+2));
    sprintf(newpath,"%s/%s",current_dir_name,dir_ptr->d_name);

    //check the type
    if((stat(newpath,&stat_buf))==-1)
      handler->Terminating_Error("Stat failed");

    //if it is a directory call recursively
    if((stat_buf.st_mode & S_IFMT)==S_IFDIR){
      Delete_dir(newpath);
    } else
      //if it is a file delete it
      remove(newpath);
    free(newpath);
  }
  // after the current dir is empty we delete it
  rmdir(current_dir_name);
}




