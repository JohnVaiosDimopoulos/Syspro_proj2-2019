#include "Cleaner.h"
#include "Argument_data.h"
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
void Cleaner::clean(Argument_data& data) {

  //1.delete id_file;
  Delete_from_common(data.getCommon_dir_name(), data.getId());
  //2. delete_mirror_recursively
  Delete_mirror_dir(data.getMirror_dir_name());

}
//==INNER-FUNCTIONALITY==//

void Cleaner::Delete_from_common(const char *common_file_name, const int id) {

  char file_path[200];
  sprintf(file_path,"%s/%d.id",common_file_name,id);
  if(remove(file_path)!=0)
    handler->Terminating_Error("Error deleting id file");
}

void Cleaner::Delete_mirror_dir(const char *mirror_dir_name) {
  if(rmdir(mirror_dir_name)==-1)
    handler->Terminating_Error("rmdir failed");
}




