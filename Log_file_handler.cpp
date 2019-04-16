#include <fstream>
#include "String_Manager.h"
#include "Log_file_handler.h"

//==Constructor==//

Log_file_handler::Log_file_handler(char *log_file_name, const int &id):id(id) {
  this->log_file_name=String_Manager::Allocate_and_copy(log_file_name);
}

Log_file_handler::~Log_file_handler() {
  free(log_file_name);
}


//==Destructor==//

void Log_file_handler::Log_Sended_file(const int &bytes_sended) {

  std::fstream log_file;
  log_file.open(log_file_name,std::fstream::app);
  log_file<<"Client: "<<id<<" Sended: "<<bytes_sended<<" bytes "<<std::endl;
  log_file.close();
}

void Log_file_handler::Log_Received_file(const int &bytes_received) {

  std::fstream log_file;
  log_file.open(log_file_name,std::fstream::app);
  log_file<<"Client: "<<id<<" Received: "<<bytes_received<<" bytes "<<std::endl;
  log_file.close();

}

void Log_file_handler::Log_Client_left(const int &client_id) {

  std::fstream log_file;
  log_file.open(log_file_name,std::fstream::app);
  log_file<<"Client: "<<client_id<<" left the system"<<std::endl;
  log_file.close();

}


