#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<ctype.h>
#define MAXLINE 1024
#define LISTENQ 10
typedef struct sockaddr SA;
int main(int argc,char **argv)
{ 
    int listenfd,connfd;
    struct sockaddr_in servaddr,cliaddr;
    char buff[MAXLINE];
    time_t ticks;
    socklen_t len;
    int port;
    int i,n;
    
    
    listenfd = socket(AF_INET,SOCK_STREAM, 0);
    port=atoi(argv[1]);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    
    bind(listenfd,(SA *) &servaddr, sizeof(servaddr));
    printf("Server is waiting at port 1234\n");
    listen(listenfd,LISTENQ);
    len=sizeof(cliaddr);
    connfd= accept(listenfd, (SA *) &cliaddr,&len);
    printf("connection from %s,port %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr,buff,sizeof(buff)), ntohs(cliaddr.sin_port));

    while(1){
        bzero(buff,sizeof(buff));
        read(connfd,buff,MAXLINE);
        printf("from Client:\n");
        fputs(buff,stdout);
        for(int i=0; i<=strlen(buff); i++)
        {
            buff[i]=toupper(buff[i]);
        }
        write(connfd,buff,sizeof(buff));
    }
    close(connfd);
}


