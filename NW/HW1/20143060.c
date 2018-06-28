// Student ID : 20143060
// Name :	Kihoon Park

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int portnum = 0;
int main(int argc, char *argv[])
{
	struct sockaddr_in server, remote;
	int request_sock, new_sock;
	int bytesread;
	int addrlen;
	int i;
	char buf[BUFSIZ];






	if (argc != 2) {
		(void) fprintf(stderr,"usage: %s portnum\n", argv[0]);
		exit(1);
	}
	if ((request_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		exit(1);
	}
	printf("Student ID : 20143060\n");
	printf("Name : Kihoon Park\n");

  // Create a Server Socket
	memset((void *) &server, 0, sizeof (server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons((u_short)atoi(argv[1]));

	if (bind(request_sock, (struct sockaddr *)&server, sizeof (server)) < 0) {
		perror("bind");
		exit(1);
	}
	if (listen(request_sock, SOMAXCONN) < 0) {
		perror("listen");
		exit(1);
	}
	while(1) {
		addrlen = sizeof(remote);
		new_sock = accept(request_sock,
			(struct sockaddr *)&remote, &addrlen);      //allow access to socket
		if (new_sock < 0) {
			perror("accept");
			exit(1);
		}
		printf("connection from host %s, port %d, socket %d\n",
			inet_ntoa(remote.sin_addr), ntohs(remote.sin_port), new_sock);

		while(1) {
			bytesread = read(new_sock, buf, sizeof (buf) - 1);

			if (bytesread<=0) {
				printf("server: end of file on %d\n", new_sock);
				if (close(new_sock))
					perror("close");
				break;
			}
			buf[bytesread] = '\0';
			printf("%s",buf);
			for(i = 0; i < bytesread; i++)
				buf[i] = toupper(buf[i]);

			char *buffer; // get my html file
			char *response_header = "HTTP/1.1 200 OK\r\n\n";
			int size;
			FILE *fp = fopen("biga.html","r"); //read my biga.html file
			fseek(fp,0,SEEK_END);              //move file pointer to EOF
			size = ftell(fp);									 //read file size
			buffer = malloc(size +1);					 //allocate buffers dynamically
			memset(buffer,0,size+1);					 //initialize buffer
			fseek(fp,0,SEEK_SET);							 //move file pointer to inception for read file
			fread(buffer,size,1,fp);					 //read file

			fclose(fp);
			printf("finish %d ",size);				 //show the number of bytes sent

			send(new_sock,response_header,strlen(response_header),0);
			send(new_sock,buffer,strlen(buffer),0);

			printf("%d\n",(int)strlen(buffer)); //show the number of the files
			free(buffer);
			//print on HTML end



		}
		//print on HTML start

	}
}
