#include <iostream>
#include "Factory.h"


int main(int argc,char** argv){

  Client_initalizer initializer = Factory::Create_Initializer();

  //we inject the dependencies in the function
  Argument_data data =initializer.Initialize(argc,argv,Factory::Create_Argument_Manager(),Factory::Create_Argument_Validator());


  Cleaner cleaner = Factory::Create_cleaner();
  cleaner.clean(data);




}