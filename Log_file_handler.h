#ifndef PROJ_2_LOG_FILE_HANDLER_H
#define PROJ_2_LOG_FILE_HANDLER_H

class Log_file_handler {

 private:
 char* log_file_name;
 const int id;
 public:
  //==Constructor-Destructor==//
  Log_file_handler(char* log_file_name,const int& id);
  virtual ~Log_file_handler();

  //==API==//
  void Log_Sended_file(const int &bytes_sended);
  void Log_Received_file(const int &bytes_received);
  void Log_Client_left(const int& client_id);


};

#endif //PROJ_2_LOG_FILE_HANDLER_H
