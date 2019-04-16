all: mirror

mirror:main.o Argument_data.o Argument_Manager.o Arguments_Validator.o Cleaner.o Client_initalizer.o Clients_List.o common_dir_monitor.o Deleter.o Error_Handler.o Factory.o Fifo_pipe_handler.o Log_file_handler.o Read_Write_handler.o Receiver.o Sender.o Signal_handler.o Status_Record.o Syncronizer.o
	g++ main.o Argument_data.o Argument_Manager.o Arguments_Validator.o Cleaner.o Client_initalizer.o Clients_List.o common_dir_monitor.o Deleter.o Error_Handler.o Factory.o Fifo_pipe_handler.o Log_file_handler.o Read_Write_handler.o Receiver.o Sender.o Signal_handler.o Status_Record.o Syncronizer.o -o mirror

main.o:main.cpp
	g++ -c main.cpp

Argument_data.o:Argument_data.cpp
	g++ -c Argument_data.cpp

Argument_Manager.o:Argument_Manager.cpp
	g++ -c Argument_Manager.cpp

Argument_Validator.o:Arguments_Validator.cpp
	g++ -c Argument_Validator.cpp

Cleaner.o:Cleaner.cpp
	g++ -c Cleaner.cpp

Client_initializer.o:Client_initalizer.cpp
	g++ -c Client_initializer.cpp

Clients_List:Clients_List.cpp
	g++ -c Clients_List.cpp

common_dir_monitor.o:common_dir_monitor.cpp
	g++ -c common_dir_monitor.cpp

Deleter.o:Deleter.cpp
	g++ -c Deleter.cpp

Error_Handler.o:Error_Handler.cpp
	g++ -c Error_Handler.cpp

Factory.o:Factory.cpp
	g++ -c Factory.cpp

Fifio_pipe_handler.o:Fifo_pipe_handler.cpp
	g++ -c Fifo_pipe_handler.c

Log_file_handler.o:Log_file_handler.cpp
	g++ -c Log_file_handler.cpp

Read_Write_handler.o::Read_Write_handler.cpp
	g++ -c Read_Write_handler.cpp

Receiver.o:Receiver.cpp
	g++ -c Receiver.cpp

Sender.o:Sender.cpp
	g++ -c Sender.cpp

Signal_handler.o:Signal_handler.cpp
	g++ -c Signal_handler.cpp

Status_Record.o:Status_Record.cpp
	g++ -c Status_Record.cpp

Syncronizer.o:Syncronizer.cpp
	g++ -c Syncronizer.cpp

