# Group2_Sprint2

****Customize and Encrypted socket connection for polling application(UseCase-Online voting management)****

This is an online vote casting system using TCP server-client program. The voters will log on from client systems and cast their votes.

**Description**

System should be secure and should only allow clients with authentic name and ID to cast the vote.

• A list of registered voters is available in a text file in the following format: Name/ID

**Complete Workflow**

The Server shall:

• First of all take the client’s name and ID and match it with the content of the text file (Voters_List.txt).

• If the details match, then it will "WELCOME VOTER" and display the names and poll symbols of the candidates on the terminal.(Candidates_List.txt)

• The voter will then cast the vote by mentioning the poll symbol (not the name) of the candidate. All these details are to be recorded in an Votes text file. 

• If there is problem of load shedding of electric light, then your system should not lose track of the votes being already casted once your server restarts again when light comes back on.

**Note**

• One client can cast a vote ONCE AND ONLY ONCE.

**How to Run**

The client.cpp and server.cpp files are provided. Just compile each file using the following command on Linux terminal or Windows Bash and run it (For client, obviously replace the server.cpp filename with client.cpp). Make sure the server is running before running any client.

g++ server.cpp -o server -lpthread
