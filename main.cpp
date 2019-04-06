#include <iostream>
#include "Factory.h"
#include "Argument_data.h"
#include "Arguments_Validator.h"
#include "Argument_Manager.h"
#include "Client_initalizer.h"
#include "Syncronizer.h"
#include "Cleaner.h"

int main(int argc,char** argv){

  Client_initalizer initializer = Factory::Create_Initializer();

  //we inject the dependencies in the function
  Argument_data data =initializer.Initialize(argc,argv,Factory::Create_Argument_Manager(),Factory::Create_Argument_Validator());
  //Syncronizer syncronizer = Factory::Create_Syncronizer();
  //syncronizer.Syncronize(data);
  Sender sender = Factory::Create_Sender();
  sender.Send_data(1,data);
  Receiver receiver = Factory::Create_Receiver();
  receiver.Receive_data(1,data);


  //Cleaner cleaner = Factory::Create_cleaner();
  //cleaner.clean(data);




}