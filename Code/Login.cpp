#include<iostream>
#include<unistd.h>
#include<fstream>
#define limit 2

using namespace std;

void Votes();
void Voters_List();
void Candidates_List();
void login()
{
	//Assigning loginAttempts initially
	int loginAttempt=0;
        string username,password;
        string choice;
        
        cout<<"Are you an admin(yes/no) : ";
        cin>>choice;
	
	if(choice=="yes")
	{
Admin:		//Asking for login with admin credentials
		cout<<"\n\t\tEnter login credentials for ADMIN PORTAL"<<endl;
                sleep(1);
                cout<<"\nEnter username : ";
		cin>>username;
		cout<<"Enter password : ";
                cin>>password;
		
		//Validating the admin credentials
		if(username=="Admin" && password=="polling")
		{
			cout<<"\n\t\t\t WELCOME TO ADMIN PORTAL"<<endl;
                        
			//Giving options for admin to check textfiles
			int admin_choice;
			char yes;
                        do
			{
				cout<<"\n PRESS "<<endl;
				cout<<"\n\t1.To check votes list"<<endl;
			        cout<<"\t2.To check Voters list"<<endl;
			        cout<<"\t3.To check Candidates list"<<endl;
                                cout<<"\n Enter your choice : ";
                                cin>>admin_choice;
                        
				switch(admin_choice)
                                {
					case 1:Votes();
					       break;

					case 2:Voters_List();
					       break;
					
					case 3:Candidates_List();
					       break;
					
					default:cout<<"\n\t\tInvalid Choice\n"<<endl;
						break;
				}
				cout<<"Do you want to continue(y/n) : ";
				cin>>yes;
			}
			while(yes=='y');
			cout<<"\n\t\t You can proceed with Casting vote "<<endl;
		        sleep(1);
		}
		else
		{
			//checking loginAttempts
			if(loginAttempt<limit)
			{
				cout<<"\n\t\t\tError !! Enter valid credentials"<<endl;
				loginAttempt++;
				
				//choice to enter credentials once
				goto Admin;
			}

			//if admin credentials are invalid upto the limit
			else
			{
				cout<<"\n\t\t\t Sorry !! Too many attempts <You have no access to login>"<<endl;
				exit(0);
			}
		}
	}
	else
	{
User:
		//Asking for login user credentials
		cout<<"\n\t\tEnter login credentials for USER PORTAL"<<endl;
                sleep(1);
                cout<<"\nEnter username : ";
                cin>>username;
                cout<<"Enter password : ";
                cin>>password;
		
                //Validating the user credentials
                if(username=="User" && password=="2022")
                {
                        cout<<"\n\t\t\tWELCOME TO USER PORTAL"<<endl;
                }
                else
                {
			//Chekcing loginAttempts
                        if(loginAttempt<limit)
                        {
                                cout<<"\n\t\t   Error !! Enter valid credentials"<<endl;
                                loginAttempt++;

				//choice to enter credentials once
				goto User;
                        }

			//if user credentilas are invalid upto the loginAttempt
                        else
			{
				cout<<"\n\t\t\t Sorry !! Too many attempts <You have no access to login>"<<endl;
                                exit(0);
                        }
                }
	}
}

//Function to open Votes textfile
void Votes()
{
	fstream file;
        file.open("Votes.txt",ios::in);
        string str;
        while(file.eof()=='\0')
        {
		getline(file,str);
                cout<<str<<endl;
        }
	//Closing file
        file.close();
}

//Function to open VotersList textfile
void Voters_List()
{
        fstream file;
        file.open("Voters_List.txt",ios::in);
        string str;
        while(file.eof()=='\0')
        {
                getline(file,str);
                cout<<str<<endl;
        }
	//closing file
        file.close();
}

//Function to open CandidateList textfile
void Candidates_List()
{
        fstream file;
        file.open("Candidates_List.txt",ios::in);
        string str;
        while(file.eof()=='\0')
        {
                getline(file,str);
                cout<<str<<endl;
        }
	//closing file
        file.close();
}
