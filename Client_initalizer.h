#ifndef PROJ_2_CLIENT_INITALIZER_H
#define PROJ_2_CLIENT_INITALIZER_H

class Arguments_Validator;
class Argument_Manager;
class Argument_data;



class Client_initalizer {

 private:
  void Write_id_file_in_common_dir(const char * common_dir_name,int id);
  void Set_up_global_var(const Argument_data& data );
  void Set_up_signal_handler();
  static void sig_handler(int signum);

 public:
  Argument_data Initialize(int argc, char **argv, Argument_Manager manager, Arguments_Validator validator);

};

#endif //PROJ_2_CLIENT_INITALIZER_H
