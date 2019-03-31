#ifndef PROJ_2_ALLOCATOR_H
#define PROJ_2_ALLOCATOR_H

#include <cstdlib>
#include <cstring>

class String_Manager{

 public:
  static char* Allocate(size_t initiali_string_size){
    char* new_string = (char*)malloc(sizeof(char)*initiali_string_size);
  }

  static char* Allocate_and_copy(const char* initial_string){
    char* new_string = (char*)malloc(sizeof(char)*(strlen(initial_string)+1));
    strcpy(new_string,initial_string);
    return new_string;
  }

};

#endif //PROJ_2_ALLOCATOR_H
