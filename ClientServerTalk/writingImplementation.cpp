 /***************************************************************************************************************************
Name: Ribash Sharma
Class: Network Programming
Instructor: Dr. Chao Zhao
Description: This file consist of implementation of two function which rea and write from the socket
***************************************************************************************************************************/

#include "writingClass.h"
#include <errno.h>
#include <stdio.h>
#include <iostream>

ssize_t writing::writen(int fd,  void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	 char *ptr;
	
	ptr = static_cast<char *> (vptr);

	nleft = n ;

	while(nleft>0)
	{
		if((nwritten = write(fd, ptr, nleft)) <= 0)
		{
			if(nwritten<0 && errno == EINTR)
				nwritten = 0;
			else
			return -1;
		}
		nleft = nleft - nwritten;
		ptr = ptr + nwritten;
	}
}

ssize_t writing:: readline(int fd, void* vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c;
	char *ptr;

	 ptr = static_cast<char *> (vptr);
	for(n =1; n< maxlen; n++)
	{
		again:
		if((rc = read(fd, &c,1)==1))
		{
			*ptr++ = c;
			if(c == '\n')
			   break;
		}else if(rc== 0)
		{
			*ptr =0;
			return(n-1);
		}else
		{
			if(errno == EINTR)
			goto again;
			return (-1);
		}
		
	}

}

