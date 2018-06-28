/*
Student ID : 20143060
Name :       Kihoon Park
*/

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

void display();


int peertcpSocket = -1;	// peer socket

int main(int argc, char **argv) {

  int tcpServ_sock;
	int new_sock;
  struct sockaddr_in tcpServer_addr;
  struct sockaddr_in tcpClient_addr;
  struct sockaddr_in newTcp_addr;

	struct hostent *hostp;
	struct servent *servp;
	struct sockaddr_in server;

  int clnt_len;

  fd_set reads, temps;
  int fd_max;
	int addrlen;

  char *tcpport = NULL;
  char *userid = NULL;

// NEED TO ADD SOME VARIABLES
	userid = argv[2];

  if(argc != 3){
    printf("Usage : %s <tcpport> <userid>\n", argv[0]);
    exit(1);
  }


  display();


	// NEED TO CREATE A SOCKET FOR TCP SERVER

  tcpServ_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset((void *) &tcpServer_addr, 0, sizeof tcpServer_addr);
	tcpServer_addr.sin_family = AF_INET;
	tcpServer_addr.sin_addr.s_addr = INADDR_ANY;
	tcpServer_addr.sin_port = htons(atoi(argv[1]));
	// NEED TO bind

	if (bind(tcpServ_sock, (struct sockaddr *)&tcpServer_addr, sizeof tcpServer_addr) < 0) {
		perror("bind");
		exit(1);
	}

	// NEED TO listen
	if (listen(tcpServ_sock, SOMAXCONN) < 0) {
		perror("listen");

		exit(1);
	}

	// initialize the select mask variables and set the
	// mask with stdin and the tcp server socket

	FD_ZERO(&reads);
	FD_SET(tcpServ_sock, &reads);
	FD_SET(fileno(stdin), &reads);

	fd_max = tcpServ_sock;
	//printf("%s\n",buf);

  printf("%s> \n", userid);
  while(1) {

    int nfound;

    temps = reads;
		//printf("find\n");

		nfound = select(fd_max+1, &temps, 0, 0, NULL);

    char command[1024] = {0,};
  	char buf[BUFSIZ] = {0,};
  	int bytesread = 0;
    char talkbuf[BUFSIZ] = {0,};
    char strbuf[1024] = {0,};
    char quitbuf[1024] = {0,};
		//printf("%d %d %d\n",FD_ISSET(tcpServ_sock, &reads),FD_ISSET(fileno(stdin), &reads),FD_ISSET(peertcpSocket, &reads));
		//printf("%d %d %d\n",FD_ISSET(tcpServ_sock, &temps),FD_ISSET(fileno(stdin), &temps),FD_ISSET(peertcpSocket, &temps));
		if(FD_ISSET(fileno(stdin), &temps)) {
    //  printf("fileno gogo\n");
      command[BUFSIZ] = '\0';
			fgets(command, sizeof (command), stdin);
			FD_CLR(fileno(stdin), &temps);


      quitbuf[1024] = '\0';
			strcpy(strbuf,command);
      //strcpy(quitbuf,command);
      strcpy(quitbuf, command);
			char localhost[1024];
			char serverport[1024];
			int k;
			char *ptr = strtok(strbuf," ");
      char *qptr = strtok(quitbuf," ");

			if(!strcmp(ptr, "@talk")){
        //printf("@talk gogo");
				//printf("%s\n",ptr);
				ptr= strtok(NULL," ");
				strcpy(localhost,ptr);
				ptr= strtok(NULL," ");
				strcpy(serverport,ptr);
				k = atoi(serverport);//serverport = ptr;

				//printf("%s %d\n",localhost,k);

				if ((peertcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
					perror("socket");
					exit(1);
				}

				static struct servent s;
				servp = &s;
				s.s_port = htons((u_short)k);
				hostp = gethostbyname(localhost);
				//printf("%s",hostp);
				//servp = gethostbyname(localhost);
				memset((void *) &server, 0, sizeof server);
				server.sin_family = AF_INET;

				memcpy((void *) &server.sin_addr, hostp->h_addr, hostp->h_length);
				server.sin_port = servp->s_port;

				if (connect(peertcpSocket, (struct sockaddr *)&server, sizeof server) < 0) {
					(void) close(peertcpSocket);
					perror("connect");
					exit(1);
				}
				FD_SET(peertcpSocket, &reads);
				if (peertcpSocket > fd_max)
					fd_max = peertcpSocket;
			}

      else if(!strcmp(qptr,"@quit\n")){
        //printf("QQQQQQQQQQQQQQQQQQQQQQ");
        close(tcpServ_sock);
        close(peertcpSocket);
        exit(1);
      }
      else {
        //printf("another command");
        //printf()
        talkbuf[BUFSIZ] = '\0';
        strcat(talkbuf,userid);
        strcat(talkbuf," : ");
        strcat(talkbuf,command);
        strcat(talkbuf,"\n");
        write(peertcpSocket,talkbuf,strlen(talkbuf));
      }
      printf("%s>\n",userid);
			// NEED TO IMPLEMENT for input from keybord
		}


		else if(FD_ISSET(tcpServ_sock, &temps)) {
			//printf(" connect request from a peer\n");
			//connect request from a peer
			addrlen = sizeof(tcpClient_addr);
			peertcpSocket = accept(tcpServ_sock,
				(struct sockaddr *)&tcpClient_addr, &addrlen);
			if (peertcpSocket < 0) {
				perror("accept");
				exit(1);
			}
			printf("connection from host %s, port %d, socket %d\n",
				inet_ntoa(tcpClient_addr.sin_addr), ntohs(tcpClient_addr.sin_port),
				peertcpSocket);

			FD_SET(peertcpSocket, &reads);
			if (peertcpSocket > fd_max)
				fd_max = peertcpSocket;
			FD_CLR(tcpServ_sock,&temps);

			//printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		}


		else if(FD_ISSET(peertcpSocket, &temps))
		{
			//printf(" message from a peer\n");
			bytesread = read(peertcpSocket,buf, sizeof(buf));
			// message from a peer
			if (bytesread<0) {
				perror("read");
				/* fall through */
			}
			if (bytesread<=0) {
				printf("Connection Closed %d\n",peertcpSocket);
				FD_CLR(peertcpSocket, &reads);
				if (close(peertcpSocket))
					perror("close");
				continue;
			}
			buf[bytesread] = '\0';
			//printf("%s: %d bytes from %d: %s\n",
			//argv[0], bytesread, peertcpSocket, buf);

      printf("%s",buf);

      /* echo it back */
			// if (write(peertcpSocket, buf, bytesread)!=bytesread){
			// 	perror("echo");
			// 	//printf("errorrrrr");
			// }
		}

  }//while End

}//main End

void display() {
	printf("Student ID : 20143060 \n");
	printf("Name : Kihoon Park  \n");
}
