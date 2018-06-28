// Student ID : 20143060
// Name : Kihoon Park

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

#define PROMPT() {printf("\n> ");fflush(stdout);}
#define GETCMD "get"
#define QUITCMD "quit"

int main(int argc, char *argv[]) {
	int socktoserver = -1;
	char buf[BUFSIZ];
	char buf2[BUFSIZ];
	char buf3[BUFSIZ];

	char fname[BUFSIZ];

	printf("Student ID : 20143060\n");
	printf("Name : Kihoon Park\n");

	PROMPT();

	for (;;) {
		if (!fgets(buf, BUFSIZ - 1, stdin)) {
			if (ferror(stdin)) {
				perror("stdin");
				exit(1);
			}
			exit(0);
		}

		char *cmd = strtok(buf, " \t\n\r");

		if((cmd == NULL) || (strcmp(cmd, "") == 0)) {
			PROMPT();
			continue;
		} else if(strcasecmp(cmd, QUITCMD) == 0) {
				exit(0);
		}

		if(!strcasecmp(cmd, GETCMD) == 0) {
			printf("Wrong command %s\n", cmd);
			PROMPT();
			continue;
		}

		// connect to a server
		char *hostname = strtok(NULL, " \t\n\r");
		char *pnum = strtok(NULL, " ");
		char *filename = strtok(NULL, " \t\n\r");

		// just for Debugging, print the URL
		//printf("%s:%s%s\n", hostname, pnum, filename);

		char fna[100];
		strcpy(fna,filename);
		// NEED TO IMPLEMENT HERE
		int h = 0;
		int scount = 0;
		int f = 0;
		for(int h = 0; h< strlen(filename)-1; h++){
			if (fna[h] == '/'){
				scount ++;
				//printf("%d\n",scount);
			}
		}
		 char *token = NULL;
		 char s2[] = "/";

		 token = strtok(fna,s2);
		 //printf("%s\n",token);
		 for(f = 0;f<scount-1;f++){
			 token = strtok(NULL,s2);
		//  printf("%s\n",token);
		 }

		struct hostent *hostp;
		struct sockaddr_in server;
		int sock;

		int bytesread;

		if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			perror("socket");
			exit(1);
		}
		hostp = gethostbyname(hostname);
		//printf("%s",hostp);
		//printf("err1");
		memset((void *) &server, 0, sizeof (server));
		server.sin_family = AF_INET;
		memcpy((void *) &server.sin_addr, hostp->h_addr, hostp->h_length);
		server.sin_port = htons((u_short)atoi(pnum));
		//server.sin_addr.s_addr = inet_addr(gethostbyname(hostname));
		//printf("err2");

		if (connect(sock, (struct sockaddr *)&server, sizeof (server)) < 0) {
			(void) close(sock);
			fprintf(stderr, "connect");
			printf("failed");
			exit(1);
		}
		int recv_data;
		int recv_len;
		char msg[500] = "GET ";
		strcat(msg,filename);
		strcat(msg," HTTP/1.0 \r\n");
		strcat(msg,"Host: ");
		strcat(msg,hostname);
		strcat(msg,"\r\n");
		strcat(msg,"User-agent: HW2/1.0\r\n");
		strcat(msg,"Connection: close\r\n\n");
		//printf("%s\n",msg);
		send(sock,msg,strlen(msg),0);
		int k;
		k = read(sock,buf2,BUFSIZ);

		//printf("%s\n",buf2);


		//printf("%d",strlen(buf));
		FILE *file = fopen("Test.txt","w");
		fprintf(file,"%s",buf2);
		//printf("%s",buf2);
		//memset(buf,0,sizeof(buf));

		int sum;
		fclose(file);
		char tmp[BUFSIZ];
		char *pstr;
		int pstr2;
		file = fopen("Test.txt","r");
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);

		fscanf(file,"%s %d",pstr,&pstr2);

		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		pstr = fgets(tmp,sizeof(tmp),file);
		//printf("%s\n",pstr);

		//printf("%d\n",pstr2);
		FILE *fp = fopen(token,"w");
		//printf("%s\n",buf2);
		//fwrite(buf2,k,1,fp);
		char* ret = NULL;
		int p = sizeof(buf2);
		//printf("%d\n",p);
		ret = strstr(buf2,"\r\n\r\n");
		ret += 4;

		char* len = NULL;
		len = strstr(buf2,"Length: ");
		len += 8;
		//printf("%s\n",len);
		FILE *zz = fopen("dummy.txt","w");
		fprintf(zz,"%s",len);
		fclose(zz);
		zz = fopen("dummy.txt","r");
		//fseek(zz,0L,SEEK_SET);
		int pa;
		int pb;
		char tmp5[BUFSIZ];
		//pa = fgets(tmp5,sizeof(pa),zz);
		fscanf(zz,"%d",&pa);
		printf("%d",pa);
		fclose(zz);

		printf("Total Size %d bytes\n",pa);

//		fscanf(file,"%s %d",pstr,&pstr2);


		//printf("Total Size %d bytes\n",pstr2);

		//printf("%s",ret);
		int z = sizeof(ret);
		//printf("%d\n",z);
		fwrite(ret,k-(ret-buf2),1,fp);
		//fwrite(buf2,k,1,fp);
		sum +=k-(ret-buf2);

		int i=0;
		int x = 0;

		int a = 10;
		while((k = read(sock,buf,BUFSIZ)) > 0){
			sum += k;
			//printf("%d %d\n",k,sum);
		  fwrite(buf,k,1,fp);
			bzero(buf,BUFSIZ);
			//printf("%d\n",sum);

			while(1){
				if(sum  >  (pa /100)*a){

					//printf("%d %d \n",sum,(pa /100)*a);
					printf("Current Downloading %d/%d (bytes) %d%%\n", sum, pa, a);
					a += 10;
					break;
				}
				break;
			}
		}

		printf("DownLoad Complete: %s %d/%d\n",token,sum,pa);
		fclose(fp);
		fclose(file);
		sum = 0;
		//get netapp.cs.kookmin.ac.kr 80 /web/member/palladio.JPG
		PROMPT();
	}

}
