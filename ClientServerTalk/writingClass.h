/***************************************************************************************************************************
Name: Ribash Sharma
Class: Network Programming
Instructor: Dr. Chao Zhao
Description: This is a header file for a class which stores the two buffers for recieving and sending characters along with 
		two readline and writen function along with the class
***************************************************************************************************************************/

#ifndef writingClass
#define writingClass
#include <stdlib.h>
#include <stddef.h>

class writing
{	public:
		char sendline[256]; 	//Char buffer which stores the input given by users
		char recline[256];	//Char buffer which stores the data send by server

		ssize_t writen(int fd,  void *ptr, size_t n);
		ssize_t readline(int fd, void* vptr, size_t maxlen);	

};

#endif

