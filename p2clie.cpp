#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/un.h>

#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define size 1024
#define PORT 9925

char rbuf[size], buf[size];
int client_fd, ret, bytes, ret;
struct sockaddr_in client_addrobj;
void *retval;

int main()
{
/**************************** Socket **********************************/
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(client_fd == -1)
		perror("Socket creation failed !!!\n");
	else
		printf("Socket created successfully \n\n");

/*************************** Naming the socket **********************************/
	client_addrobj.sin_family = AF_INET;
	client_addrobj.sin_port = htons(PORT);
	client_addrobj.sin_addr.s_addr = inet_addr("127.0.0.1");

/**************************** Connect *********************************/
	ret = connect(client_fd, (struct sockaddr *)&client_addrobj, sizeof(client_addrobj) );
	if(ret == -1)
		perror("Connection failed !!!\n");
	else
		printf("Connection established successfully \n\n");

/***************************** Conversation **********************************/

		bzero(rbuf, size);
		while(strncmp(rbuf, "end", 3) != 0 )
		{
			bzero(rbuf, size);
			printf("\nEnter the message from client....\n");
			
			fgets(rbuf, size, stdin);
			bytes = send(client_fd, rbuf, sizeof(rbuf), 0);

			if(bytes == -1)
				
				perror("Writing by the client failed!!!\n");
			else
				printf("String sent\n");

			bzero(buf, size);
			bytes = recv(client_fd, buf, size, 0);
			if(bytes == -1)
				perror("Reading from server failed!!!\n");
			else
				printf("\nYou got the reversed string from server :\n  %s \n", buf);
			
		}
		printf("\n***************** Conversation Over *******************\n");
	close(client_fd);
return 0;
}

