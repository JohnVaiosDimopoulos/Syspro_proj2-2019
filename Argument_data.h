#ifndef PROJ_2_ARGUMENT_DATA_H
#define PROJ_2_ARGUMENT_DATA_H

class Argument_data {
 private:

  char* common_dir_name;
  char* input_dir_name;
  char* mirror_dir_name;
  char* log_file_name;
  int id,buffer_size;

 public:
  //==constructor-destructor==//
  Argument_data();
  ~Argument_data();

  //==setters-getters==//
  char *getCommon_dir_name() const;
  void setCommon_dir_name(char *common_dir_name);
  char *getInput_dir_name() const;
  void setInput_dir_name(char *input_dir_name);
  char *getMirror_dir_name() const;
  void setMirror_dir_name(char *mirror_dir_name);
  char *getLog_file_name() const;
  void setLog_file_name(char *log_file_name);
  const int getId() const;
  const int getBuffer_size() const;
  void setId(int id);
  void setBuffer_size(int buffer_size);

};

#endif //PROJ_2_ARGUMENT_DATA_H
