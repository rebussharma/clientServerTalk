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
//************************************************************************************************************************

void str_cli(FILE *fp, int sockfd)
{
        
	writing test; //Declaring an object from the writing class 

        while (fgets(test.sendline, 256, fp) != NULL) //asking the user and input and storing it in a sendline buffer
	{

                test.writen(sockfd, test.sendline, strlen(test.sendline)); // writing the user input in thesocket

                if (test.readline(sockfd, test.recline, 256) == 0) // reading the input from server
                        cout<<"str_cli: server terminated prematurely"<<endl;

                fputs(test.recline, stdout); //displaying the buffer send by server in the screen
		
		/**************setting both buffers to zero********************/
		
		memset(test.recline, 0 ,256);
		memset(test.sendline,0 ,256);
        }
}

//********************************************************************************
int main(int argc, char **argv)
{
        int  sockfd;
        struct sockaddr_in servaddr;

        if (argc != 2) //checking the user argument
                cout<<"usage: tcpcli <IPaddress>"<<endl;

        sockfd = socket(AF_INET, SOCK_STREAM, 0); //calling socket function to establish a scoket

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(12345);
        inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

        connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)); //calling connect function to connect to the socket

        str_cli(stdin, sockfd); //function to start talk application after client and server are connected        

        exit(0);
}

