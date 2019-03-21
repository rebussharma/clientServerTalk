/***************************************************************************************************************************
Name: Ribash Sharma
Class: Network Programming
Instructor: Dr. Chao Zhao
Description: This is a client side of a talk application
***************************************************************************************************************************/

//***********************************************Libraries****************************************************************
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include "writingClass.h"
using namespace std;

//**************************************************************************************************************************
void str_echo(int sockfd, FILE *fp)
{
	writing test; // Declaring a object to store the buffer
	again:
	ssize_t n;
	memset(test.recline, 0, 256);
	while((n = test.readline(sockfd, test.recline, 256))>0)//Reads the character buffer from readline and stores in the recline
	{
		fputs(test.recline, stdout);	//Displays the output

		fgets(test.sendline, 256,fp);	//Asks user for input
		test.writen(sockfd,test.sendline, strlen(test.sendline));	//Writes in the sockets
		memset(test.sendline,0 , 256);	//Resets the character array
		memset(test.recline, 0 ,256);	//Resets the character array
		
		if(n<0 && errno == EINTR)
		{	
			goto again;
		}
		else if(n<0)
		{
			cout<<"REad error"<<endl;
		}
	}
}

int main(int argc, char ** argv)
{	
	int listenfd, connfd;
	pid_t childpid;
	struct sockaddr_in cliaddr, servaddr;
	socklen_t clilen;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family= AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(12345);

	bind(listenfd, (struct sockaddr * ) &servaddr, sizeof(servaddr)); 

	listen(listenfd, 20); // Makes the server to the listen state

	for(; ;)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
	
		if((childpid= fork())==0)
		{
			close(listenfd);
			str_echo(connfd,stdin);
			exit(0);
		}
	
		close(connfd);
	}
	
	return 0;
}
