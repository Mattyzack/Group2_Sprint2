#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<bits/stdc++.h>
#include<string.h>
#include<iostream>
#include <iostream>


using namespace std;

int port_number = 2007;

int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[2000], client_message[2000];
	
	//Cleaning the Buffers	
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	//Creating Socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socket_desc < 0)
	{
		cout<<"Could Not Create Socket. Error!!!!!\n";
		return -1;
	}
	
	cout<<"Socket Created\n";
	
	//Specifying the IP and Port of the server to connect
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//------------------------------------------------------------------------------------------------//
	
    //Now connecting to the server accept() using connect() from client side
	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		cout<<"Connection Failed. Error!!!!!";
		return -1;
	}
 
	//Receive the connection message back from the server		
	if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
	{
		cout<<"Receive Failed. Error!!!!!\n";
		return -1;
	}
	
	cout<<"Server Message:\n\n"<<server_message;
	
	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));				

	//Get Input from the User
	cout<<"Enter your name and Voter's ID in format (Hardik pandya/35601-4426749-2): ";
	fgets(client_message, 200, stdin);

	//Send credentials back to Server	
	if(send(socket_desc, client_message, strlen(client_message),0) < 0)
	{
		cout<<"Send Failed. Error!!!!\n";
		return -1;
	}		

	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));				

	
	//Receive the message back from the server		
	if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
	{
		cout<<"Receive Failed. Error!!!!!\n";
		return -1;
	}

	cout<<"Server Message: \n"<<server_message;

	if (strcmp(server_message, "Sorry! Your name is not in the authorized voters list.\n") != 0)
	{
		cout<<"hi1234";
		//Receive the message back from the server		
		if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
		{
			cout<<"Receive Failed. Error!!!!!\n";
			return -1;
		}

		cout<<"Server Message: \n\n"<<server_message;

		if (strcmp(server_message, "Sorry! You have already casted a vote. You can't vote again.\n") == 0)
		{
			cout<<"hii";
                        
                        exit(0);
                }
                else{
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));				

			//Get Input Symbol from the User	
			cout<<"\n Enter the candidate's symbol: ";
			fgets(client_message, 200, stdin);
		
			//Send the symbol back to server			
			if(send(socket_desc, client_message, strlen(client_message),0) < 0)
			{
				cout<<"Send Failed. Error!!!!\n";
				return -1;
			}		
			
			//Receive confirmation from server		
			if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
			{
				cout<<"Receive Failed. Error!!!!!\n";
				return -1;
			}

			cout<<"Server Message: \n\n"<<server_message;
		}			
	}
	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
				

        //receiving result declaration
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
	{
		cout<<"Receive Failed. Error!!!!!\n";
		return -1;
	}
        cout<<"Server Message: \n\n"<<server_message;

        
        

	//Closing the Socket
	close(socket_desc);
	return 0;
}
