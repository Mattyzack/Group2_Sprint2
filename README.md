# Group2_Sprint2

Online Voting System using TCP Sockets

This is an online vote casting system using TCP multithreaded server-client program. The voters will log on from client systems and cast their votes.

Description
System should be secure and should only allow clients with authentic name and CNIC to cast the vote.

• A list of registered voters is available in a text file in the following format: Name/CNIC number

Complete Workflow
The Server shall:

• First of all take the client’s name and CNIC and match it with the content of the text file (Voters_List.txt).

• If the details match, then it will welcome the voter and display the names and poll symbols of the candidates on the terminal.(Candidates_List.txt)

• The voter will then cast the vote by mentioning the poll symbol (not the name) of the candidate. All these details are to be recorded in an output text file. This system should work perfectly for at least 5 different clients at the same time.

• If there is problem of load shedding of electric light, then your system should not lose track of the votes being already casted once your server restarts again when light comes back on.

• Assume that when the record of votes will be written by one thread in an output file, no other thread will make a read to the output file.

Note
• One client can cast a vote ONCE AND ONLY ONCE.

• The Server should allocate a new thread for every new incoming Client.

How to Run
The client. and server.c files are provided. Just compile each file using the following command on Linux terminal or Windows Bash and run it (For client, obviously replace the server.c filename with client.c). Make sure the server is running before running any client.

gcc –pthread server.c -o server.out
