/************************************************************************/
/*   PROGRAM NAME: client.c  (works with serverX.c)                     */
/*                                                                      */
/*   Client creates a socket to connect to Server.                      */
/*   When the communication established, Client writes data to server   */
/*   and echoes the response from Server.                               */
/*                                                                      */
/*   To run this program, first compile the server_ex.c and run it      */
/*   on a server machine. Then run the client program on another        */
/*   machine.                                                           */
/*                                                                      */
/*   COMPILE:    gcc -o client main.c -lnsl -lpthread                   */
/*   TO RUN:     client  server-machine-name                            */
/*                                                                      */
/************************************************************************/

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

int term = 0;

void* listenThread( void* arg);

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

    //while( scanf( "%s", buf) != EOF)
    while (1)
    {
      buf[0] = '\r';
      buf[1] = '\n';
      buf[2] = '\0';
      c = getchar();
      i = 0;
      while(c != '\n')
      {
        //printf("i : %d\n", i);
        buf[i] = (char)c;
        buf[i+1] = '\r';
        buf[i+2] = '\n';
        buf[i+3]= '\0';
        //putchar(c);
        i = i + 1;
	c = getchar();
      }
      printf("WRITING : %s\n", buf);
      write(sd, buf, i+2);

    }
    term = 1;
    close(sd);
    return(0);
}

void* listenThread( void* arg)
{
  int sd = (*((int*)arg));
  char buf[1024];
  int n, i, j;
  while (!term)
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
    }
    pthread_yield();
  }
  printf("End listen thread");
}


