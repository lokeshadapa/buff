#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

typedef struct sockaddr_in sckadr;
int main(int argc,char **argv)
{
	int port=atoi(argv[1]);//converting port to integer.
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	printf("socket failed\n");
	sckadr seradr;
	seradr.sin_family=AF_INET;
	seradr.sin_port=htons(port);//sets the port number to defined sata type.
	seradr.sin_addr.s_addr=htonl(INADDR_ANY);//giving ip address.
	bzero(seradr.sin_zero,8);//filler must be set to all zero.
	int m=bind(sfd,(struct sockaddr *)&seradr,sizeof(seradr));//associating the socket to the server
	if(m<0)
	printf("bind failed");
	socklen_t clen;//declaring client socket_length.
	sckadr cadr;//declaring client socket address.
	int n=listen(sfd,1);//the srever announces that it is willing to accept connections.the number gives the limit of connections to be held in queue
	while(1)
	{
		int nsfd=accept(sfd,(struct sockaddr *)&cadr,&clen);//connection is accepted by server
		if(nsfd>=0)
		{
			printf("entered \n");
			int pid=fork();
			if(pid==0)//child
			{
				close(sfd);
				while(1)
				{
					char *buf=new char[1024];
					int r=recv(nsfd,buf,1024,0);
					printf("%s\n",buf);
					r=send(nsfd,buf,strlen(buf),0);
					//bzero(buf,1024);
				}
			}
			else//parent
			{
				close(nsfd);
			}
		}
	}
}

