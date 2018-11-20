/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argsize, char *args[])
{
    int sockfd;
    int len,i;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    int id=atoi(args[1]);
    time_t realtime;

/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: CLIENT3");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    
    write(sockfd, &id, sizeof(id));
    //write(sockfd, &parar, sizeof(parar));
    while(1){
    	read(sockfd, &realtime,sizeof(time_t));
    	printf("Client %d Time from server = %s\n", id, asctime(localtime(&realtime)));
	sleep(1);
    }
    write(sockfd, &id, sizeof(id));
    close(sockfd);
exit(0);
}
