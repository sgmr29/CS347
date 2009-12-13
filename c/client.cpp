/************************************************************************/
/*   File Name: client.cpp                                              */
/*                                                                      */
/*   Client uses sockets to connect to the fibs.com server, and         */
/*     hopefully it also plays backgammom.                              */
/*                                                                      */
/*   Portions of this code were borrowed from code posted at            */
/*      http://web.mst.edu/~ercal/284/284.html                          */
/************************************************************************/

/*
    This file is part of CS347Backgammon.

    CS347Backgammon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CS347Backgammon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CS347Backgammon.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>


#include <pthread.h>

#define SERVER_PORT 4321     /* define a server port number */

#define _COMPILING_QBZCIXTPRE
#include "client.h"
#include "AI.h"



void* listenThread( void* arg);

AI myAI;

int main( int argc, char* argv[] )
{
    int sd;
    struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) };
    char buf[1024];
    struct hostent *hp;
    pthread_t tid;
    int BUF_SIZE = 1023;
    int c, i;

    if( argc != 2 )
    {
	printf( "Usage: %s hostname\n", argv[0] );
	return 1;
    }

    /* get the host */
    if( ( hp = gethostbyname( argv[1] ) ) == NULL )
    {
	printf( "%s: %s unknown host\n", argv[0], argv[1] );
	return 1;
    }
    bcopy( hp->h_addr_list[0], (char*)&server_addr.sin_addr, hp->h_length );

    /* create a socket */
    if( ( sd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
	perror( "client: socket failed" );
	return 1;
    }




    /* connect a socket */
    if( connect( sd, (struct sockaddr*)&server_addr,
		 sizeof(server_addr) ) == -1 )
    {
	perror( "client: connect FAILED:" );
	return 1;
    }

    printf("connect() successful! will send a message to server\n");
    printf("Input a string:\n" );

    //fcntl(sd, F_SETFL, O_NONBLOCK);
    pthread_create(&tid, NULL, listenThread, &sd);

    myAI.console(sd);

    //while( scanf( "%s", buf) != EOF)

    close(sd);
    return(0);
}

void* listenThread( void* arg)
{
  int sd = (*((int*)arg));
  char buf[1024];
  int n, i, j;
  while (1)
  {
    n = read(sd, buf, sizeof(buf)-1);
    for (i = 0; i < n; i++)
    {
      if (buf[i] == (char)255)
      {
        printf("RECV COMMAND : %d %d\n",
        (unsigned char)buf[i+1],
        (unsigned char)buf[i+2]);

        // Remove those characters from the input text.
        for (j = i; j < n-3; j++)
        {
          buf[i] = buf[i+3];
        }
        n -= 3;
      }
    }
    if (n > 0)
    {
      buf[n] = '\0';
      printf("RECV TEXT: %s\n", buf);
      myAI.parse(buf);
    }
    pthread_yield();
  }
  printf("End listen thread");
}


