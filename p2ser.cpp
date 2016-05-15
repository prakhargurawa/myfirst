#include<stdio.h>
#include<string.h>
#include<sys/un.h>
#include<unistd.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define size 1024
#define PORT 9925

char rbuf[size];
void *retval;
int server_fd, c_fd, ret, c_len, bytes, ret;
struct sockaddr_in server_addrobj, c_addrobj;

void strrev(char *s)
{
	int i, j;
	char t;
	for(i=0; s[i]!='\0'; i++);

	j=0;i--;
	while(j<i)
	{
		t = s[i];
		s[i] = s[j];
		s[j] = t;

		j++;i--;
	}
}
int main()
{
	int true = 1;

/*************************** Unlink *********************************/

	unlink("SOCKET SERVER");

/******************************* Socket **********************************/

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));
	if(server_fd == -1)
		perror("Socket creation failed!!!\n");
	else
		printf("Socket created successfully\n");

/****************************** Bind ***************************************/

	server_addrobj.sin_family = AF_INET;
	server_addrobj.sin_port = htons(PORT);
	server_addrobj.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(server_fd, (const struct sockaddr *)&server_addrobj, sizeof(server_addrobj));
	if(ret==-1)
		perror("Binding failed !!!!\n");
	else
		printf("Binding Successfull\n");

/**************************** Listen *************************************/

	ret = listen(server_fd, 5);
	if(ret==-1)
		perror("Listening failed!!!\n");
	else
		printf("Listening successfull\n");

/*********************************** Accept *********************************/

	while(1)
	{
		bzero(rbuf, size);

		printf("\nWaiting for client request.......\n");
		
		c_len=sizeof(c_addrobj);
		c_fd = accept(server_fd, (struct sockaddr *)&c_addrobj, &c_len);

		if(c_fd == -1)
			perror("Accept system call failed!!!\n");
		else
			printf("Connection established successfully \n");

/*****************************Conversation*****************************/

		bzero(rbuf, size);
		while(strncmp(rbuf, "end", 3) != 0 )
		{
			bzero(rbuf, size);
			bytes = recv(c_fd, rbuf, size, 0);

			if(bytes == -1)
				perror("Writing by the server failed!!!\n");
			strrev(rbuf);
			bytes = send(c_fd, rbuf, sizeof(rbuf), 0);
			if(bytes == -1)
				perror("\nWriting by the server failed!!!\n");
			else
				printf("\nString reversed and sent      \n");

		}
		printf("\n***************** Conversation Over *******************\n");	
		close(c_fd);
	}
	close(server_fd);
return 0;
}
