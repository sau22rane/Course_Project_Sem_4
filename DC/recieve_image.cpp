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

void decode_nrzi(char*,char*,int);

int main()
{
    int sockfd, port_no, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256], ip_address[20], port_char[10];
    
    printf("Enter IP adderss of server: ");
    scanf("%s",ip_address);
    scanf("%*c");
    printf("Enter port number for communication: ");
    scanf("%d",&port_no);
    scanf("%*c");

    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        printf("ERROR opening socket");
    server = gethostbyname(ip_address);
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
    char dataToBeRead[55], decoded[55];
    
    if(strcmp(buffer,"OK")==0){
        //Read image 
        n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
    
        fpwrite = fopen(dataToBeRead, "wb") ; 
        
        if ( fpwrite == NULL ) 
        { 
            printf( "File failed to open." ) ; 
        } 
        else{
        int i=0;
        n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
        decode_nrzi(dataToBeRead,decoded,55);
        while(strcmp(decoded,"CLOSE")){
            
            n = write(sockfd, "1", strlen("1"));
            fwrite(decoded,1,sizeof(decoded),fpwrite);
            n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
            decode_nrzi(dataToBeRead,decoded,55);
        }
        }
        printf("\nClosing Socket\n");

    }

    fclose(fpwrite);
    close(sockfd);
    return 0;
}

void decode_nrzi(char *encoded, char *decoded, int size){
    int i,j,val,prev,temp;
    for(j = 0;j<size;j++){
        temp=0;
        for(i = 0; i <= 7; i ++){
            
            val = (encoded[j] >> i) & 0x01;
            if(i==0){
                prev = val;
                temp = prev;
            }
            else{
                if(val == prev){
                    temp = temp+(0<<i);
                    prev = val;
                }
                else{
                    temp = temp+(1<<i);
                    prev = val;
                }
            }
        }
        decoded[j] = temp;
    }
}