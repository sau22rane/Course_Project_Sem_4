#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>



int main(int argc, char *argv[])
{
    int sockfd, port_no, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       printf("usage %s hostname port\n");
       exit(0);
    }
    port_no = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        printf("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        printf("ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port_no);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        printf("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    /* n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) 
         printf("ERROR writing to socket"); */
    bzero(buffer,256);

    n = read(sockfd, buffer, 255);
    if (n < 0) 
         printf("ERROR reading from socket");
    printf("Message Recieved: %s\n", buffer);
    if(strcmp(buffer,"START")==0)
    {
        printf("It works\n");
        char buf[] = "INITIATE_SEND";
        n = write(sockfd, buf, strlen(buf));

    }
    n = read(sockfd, buffer, 255);
    if (n < 0) 
         printf("ERROR reading from socket");
    printf("Message Recieved: %s\n", buffer);



    FILE *fpwrite ; 
    char dataToBeRead[55];

    if(strcmp(buffer,"OK")==0){
        //Read image 
        
    
        fpwrite = fopen("Images/trial.jpg", "wb") ; 
        
        if ( fpwrite == NULL ) 
        { 
            printf( "GfgTest.c file failed to open." ) ; 
        } 
        else{
        int i=0;
        n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
        while(strcmp(dataToBeRead,"CLOSE")){
            printf( "%s" , dataToBeRead ) ; 
            i++;
            fwrite(dataToBeRead,1,sizeof(dataToBeRead),fpwrite);
            n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
        }
        }

    }

    fclose(fpwrite);
    close(sockfd);
    return 0;
}
