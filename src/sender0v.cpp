//============================================================================
// Name        : socketTest.cpp
// Author      : Jules
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h> //For manipulating strings of the sockaddr structure (bzero)
#include <netdb.h>
#include <sys/socket.h> //For sockets and struct addr
#include <sys/types.h> //Data types on socket structs
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/chrono.hpp>
//#include <boost/timer.hpp>
//#include <boost/timer/timer.hpp>
//#include <boost/thread.hpp>
#define BUFSIZE 5
#define PORT 4321
#define NUMMSG 3000000//How many messages we want to send

//using namespace std;

int main() {

	//Declaration of the struct
	struct sockaddr_in hostAddr, recvAddr;
	char *server = "127.0.0.1";
	char buffer[BUFSIZE];
	int result = 0;

	for (int i = 0; i < BUFSIZE; i++)
	{
		buffer[i]='i';
	}
	//let's go for the receiver's socket
	int sd = (socket(AF_INET, SOCK_DGRAM, 0));
	if ( sd < 0 ){
		perror("Error creating socket");
		return 0;
	}

	//Now, let's set the sockaddr struct to zero
	bzero(&hostAddr, sizeof(hostAddr));

	//Bind the socket, give it a 'name', an address for it - sending this info from host to network.
	//First, fill the socked structure
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = htonl(INADDR_ANY); //get any IP address available
	hostAddr.sin_port = htons(0); //same for the port
	int binder = bind(sd, (struct sockaddr *)&hostAddr, sizeof(hostAddr));
	if ( binder < 0 ){
		 perror("Error binding socket");
		 return 0;
	}

	//Establish in the sender which is the receiver addres: PORT, IP in presentation format.
	bzero(&recvAddr, sizeof(recvAddr));
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_addr.s_addr = htonl(INADDR_ANY); //get any IP address available
	recvAddr.sin_port = htons(PORT); //Get the specified port. See define. Same as defined in receiver
	//IP address in presentation format from 'char server' to network
	int okAddr = inet_pton(AF_INET, server, &recvAddr.sin_addr);
	if (okAddr < 1){
		perror("Error IP address");
				return 0;
			}

	//Let's send the messages
	boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();

	for (int i = 0; i <= NUMMSG; i++){
			std::cout << "Sending packet "<< i << " to " << PORT << " at machine " << server << std::endl;
			sendto( sd, buffer, strlen(buffer), 0, (struct sockaddr *)&recvAddr, sizeof(recvAddr) );
			//usleep(1);
			if (i)result += 1;


	}
	boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration timeTaken = end - start;
	std::cout << "tiempo ejecucion: " << timeTaken << std::endl;
	std::cout << result << std::endl;
	assert(result == NUMMSG);
	close(sd); //close socket
	return 0;
}
