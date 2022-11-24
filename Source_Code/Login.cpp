#include<iostream>
#include<unistd.h>

using namespace std;




void login()
{
   
   
    int loginAttempt=0;
    string username,password;
    
    
string choice;

cout<<"Are you an admin(yes/no) : ";
cin>>choice;


if(choice=="yes")
{
    label1:
cout<<"\n\t\tEnter login credentials for ADMIN PORTAL"<<endl;
                sleep(1);
cout<<"\nEnter username : ";
cin>>username;
cout<<"Enter password : ";
                cin>>password;

if(username=="Admin" && password=="polling")
{
cout<<"\n\t\t\tWELCOME TO ADMIN PORTAL"<<endl;
}
else
{
if(loginAttempt<2)
{
cout<<"\n\t\t\tError !! Enter valid credentials"<<endl;
loginAttempt++;
//admin();
goto label1;
}
else
{
cout<<"\n\t\t\t Sorry !! Too many attempts <You have no access to login>"<<endl;
exit(0);
}
}

}



else
{
    label2:
cout<<"\n\t\tEnter login credentials for USER PORTAL"<<endl;
                sleep(1);
cout<<"\nEnter username : ";
                cin>>username;
                cout<<"Enter password : ";
                cin>>password;

                if(username=="User" && password=="2022")
                {
                        cout<<"\n\t\t\tWELCOME TO USER PORTAL"<<endl;
                }
                else
                {
                        if(loginAttempt<2)
                        {
                                cout<<"\n\t\t\tError !! Enter valid credentials"<<endl;
                                loginAttempt++;
                              goto label2;
                               // user();
                        }
                        else
                        {
                        cout<<"\n\t\t\t Sorry !! Too many attempts <You have no access to login>"<<endl;
                        exit(0);
                        }
                }
}
}





