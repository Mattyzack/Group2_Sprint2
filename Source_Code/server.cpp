#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<bits/stdc++.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include <pthread.h>
#include <cstdint>
#include "Logger.h"
#include <sstream>
#include <string>
#include "header.h"

using namespace std;

int port_number = 2007;

void *communicate (void *message)
{
	int client_sock =  (long) message  ;
	char server_message[2000], client_message[2000];
	
	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
    

	//--------------------------------------------------------------------------//	
	// Take name and CNIC from client

	//Receive Name/CNIC from the client
	if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
	{
		cout<<"1 Receive Failed. Error!!!!!\n";
	Logger::Error(__FILE__,__LINE__,"SERVER ERROR");

	}
	
	char credentials[255];
	strcpy(credentials, client_message);

	//remove newline character
	char *newline;
	newline = strchr(credentials,'\n');
	if(newline != NULL)
		*newline = '\0';
	
	// Read Voters_List.txt and match CNIC and name, if match_exists then allow to vote else end thread
	//FILE *fp;
	
	//fp = fopen("./Voters_List.txt", "r");

     
        char buff[255];
        ifstream ifile;
	string line;

        ifile.open("Voters_List.txt");
	int voter_found = 0;
	
	//while(fgets(buff, sizeof(buff), fp) != NULL)
        while(getline(ifile, line))
	{	
		//remove newline and carriage return characters
		char *newline,*carriage_return;
		strcpy(buff,line.c_str());
		newline = strchr(buff,'\n');
		if(newline != NULL)
			*newline = '\0';

		carriage_return = strchr(buff,'\r');
		if(carriage_return != NULL)
			*carriage_return = '\0';	
	
		if (strcmp(credentials, buff) == 0)
		{
			voter_found = 1;
			break;
		}		
	}
	
	ifile.close();

	// Check if this client has already casted a vote or note. If yes, then end thread
	if (voter_found == 1)
	{
		//Cleaning the Buffers        
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));

		//Send a greeting message back to client
		strcpy(server_message, "Welcome Voter.\n");

		if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
			cout<<"1 Send Failed. Error!!!!!\n";
			Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
		}	       

		//fp = fopen("./Votes.txt", "r");
              
                ifile.open("Votes.txt");
		
		int vote_casted = 0;
		
		//while(fgets(buff, 200, fp) != NULL)
		while(getline(ifile,line))
		{
			//parse string
			char *temp_comma;
			strcpy(buff,line.c_str());
			temp_comma = strchr(buff,',');
			if(temp_comma != NULL)
				*temp_comma = '\0';
						
			if (strcmp(credentials, buff) == 0)
			{
				vote_casted = 1;
				break;
			}		
		}
		
		//fclose(fp);

                ifile.close();
		
		//vote not casted previously, so allow to cast vote
		if (vote_casted == 0)
		{
			//display candidates list
			//fp = fopen("./Candidates_List.txt", "r");

                        ifile.open("Candidates_List.txt");
								
			char candidates[1000];
			
			strcpy(candidates, "Following are the list of candidates and their symbols: \n");
			//send(client_sock,msg, strlen(msg)+1,0);
			
			//while (fgets(buff, sizeof(buff), fp) != NULL)
			while(getline(ifile,line))
			{
				strcpy(buff,line.c_str());
				strcat(candidates,buff);
				
			}
			strcpy(server_message, candidates);

			if (send(client_sock, server_message, strlen(server_message),0)<0)
			{
				cout<<"2 Send Failed. Error!!!!!\n";
				Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
			}
			
			//fclose(fp);
                         
		
                        ifile.close();
			//send candidates data back to client
			
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));

				       
			

			/*//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));*/

			//Receive candidate's symbol from client
			if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
			{
				cout<<"2 Receive Failed. Error!!!!!\n";
				Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
			}
			
			//write this vote in Votes.txt
			char symbol[100];
			strcpy(symbol, client_message);

			char vote[200];
			strcpy(vote, credentials);
			strcat(vote, ",");
			strcat(vote, symbol);
			
			
			//fp = fopen("./Votes.txt", "a");
			ofstream ofile;
                        
                        ofile.open("Votes.txt", ios::app);
			ofile << vote <<endl;
                        
                        
			//fputs(vote, fp);
			//fclose(fp);
                        ofile.close();

			//send a vote casted message back to client
			
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));

			strcpy(server_message, "Congratulations! You have succesfully casted your vote.\n");

			if (send(client_sock, server_message, strlen(server_message),0)<0)
			{
				cout<<"3 Send Failed. Error!!!!!\n";
				Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
			}	       						
		}
		else
		{
			//Cleaning the Buffers        
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));

			strcpy(server_message, "Sorry! You have already casted a vote. You can't vote again.\n");
			
			int sender=(send(client_sock, server_message, strlen(server_message),0));

			if (sender<0)
			{
				cout<<"4 Send Failed. Error!!!!!\n";
				Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
				
			}
			
			      
		}	
	}
	else
	{
		//Cleaning the Buffers        
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));

		strcpy(server_message, "Sorry! Your name is not in the authorized voters list.\n");

		if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
			cout<<"5 Send Failed. Error!!!!!\n";
			Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
		}	       
	}
	
	//------------------------------------------------------------------------------//


        

	


	//string username, passwd;
	//string user_name, pass_wd;

	ifstream afile;

	string smb1="Bat";
	string smb2="Tiger";
	string smb3="Arrow";

	int sm1=0; //bat
	int sm2=0; //tiger
	int sm3=0; //arrow

	char arr[100];
	string s1,s2;

	afile.open("Votes.txt");
	while(getline(afile, line))
	{
		//stringstream strm(line);
		//strm >> user_name >>pass_wd;
	
	         stringstream strm(line);
                 getline(strm,s1,',');
                  
                 getline(strm,s2);
	
		if( (smb1 ==s2))
		{
			sm1++;
		}
		else if( (smb2 == s2))
		{
			sm2++;
		}
		else if( (smb3 == s2))
		{
			sm3++;
		}

}

//cout<<sm1<<"\n"<<sm2<<"\n"<<sm3<<"\n";

if(sm1>sm2 && sm1>sm3){
    //"sm1 is the winner";
    strcpy(server_message,"sm1 is the winner" );
    if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
		   cout<<" Send Failed. Error!!!!!\n";
		   Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
		}
    
}

else if (sm2>sm1 && sm2>sm3){
    //"sm2 is the winner";
    strcpy(server_message,"sm2 is the winner" );
     if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
		   cout<<" Send Failed. Error!!!!!\n";
		   Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
		}
}

else if (sm3>sm1 && sm3>sm2){
    //"sm3 is the winner";
    strcpy(server_message,"sm3 is the winner" );
     if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
		   cout<<" Send Failed. Error!!!!!\n";
		   Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
		}
}

else{
   
    strcpy(server_message,"Tie situation" );
     if (send(client_sock, server_message, strlen(server_message),0)<0)
		{
		   cout<<" Send Failed. Error!!!!!\n";
		   Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
		}
}

	close(client_sock);
	pthread_exit(NULL); 


}




int main(void)
{






login();







	int socket_desc, client_sock, client_size; 
	struct sockaddr_in server_addr, client_addr;
	char server_message[2000], client_message[2000];
	
	//Cleaning the Buffers        
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	//Creating Socket	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socket_desc < 0)
	{
		cout<<"Could Not Create Socket. Error!!!!!\n";
		Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
		return -1;
	}
	
	cout<<"Socket Created\n";
	
	//Binding IP and Port to socket        
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
	{
			cout<<"Bind Failed. Error!!!!!\n";
			Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
			return -1;
	}        
	
	cout<<"Bind Done\n";
	
	//Put the socket into Listening State        
	if(listen(socket_desc, 1) < 0)
	{
			cout<<"Listening Failed. Error!!!!!\n";
			Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
			return -1;
	}
	
	cout<<"Listening for Incoming Connections.....\n";
	Logger::Info(__FILE__,__LINE__,"SERVER Listening for Incoming Connections.... ");
	
	//------------------------------------------------------------------------------//
	while (1)
	{		
		//Accept the incoming Connections	
		socklen_t len = sizeof(client_addr);
		client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &len);
	
		if (client_sock < 0)
		{
			cout<<"Accept Failed. Error!!!!!!\n";
			Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
			return -1;
		}
		
		printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		Logger::Info(__FILE__,__LINE__,"SERVER Client Connected with IP: %s and Port No: ");
		
		strcpy(client_message, "Connection Established!");

		// Send the connection message back to client
		if (send(client_sock, client_message, strlen(client_message),0)<0)
		{
			cout<<"5 Send Failed. Error!!!!!\n";
			Logger::Error(__FILE__,__LINE__,"SERVER ERROR");
			return -1;
		}
		
		//Cleaning the Buffers        
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));
		
		pthread_t thread1;

			
		//create new thread for each client
		pthread_create(&thread1,NULL,communicate,(void*)client_sock);
	    
                         	
		
	}
            
	//Closing the Socket        
	close(socket_desc);
	return 0;       
}
