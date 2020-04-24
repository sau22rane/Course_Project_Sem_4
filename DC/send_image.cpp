#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void encode_nrzi(char*,char*,int);

int main(){
    int sockfd, newsockfd, port_no, n;
    socklen_t clilen;
    char buffer[256];
    int opt = 1;
    char ip_address[20], name[20];
    struct sockaddr_in serv_addr, cli_addr;
    /* if (argc < 2) {
        printf("ERROR, no port provided\n");
        exit(1);
    } */

    printf("Enter the IP address of this PC: ");
    scanf("%s",ip_address);
    printf("Enter the port number: ");
    scanf("%d",&port_no);

    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        printf("ERROR opening socket");
    printf("All Good");

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        printf("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
        /* The bzero() function erases the data in the n bytes of the memory
        starting at the location pointed to by s, by writing zeros (bytes 
        containing '\0') to that area. */
    bzero((char *) &serv_addr, sizeof(serv_addr));
        /* The C library function int atoi(const char *str) converts the string 
        argument str to an integer (type int). */
    //port_no = atoi(argv[1]);
        /* AF_INET      		IPv4 Internet protocols  */
    serv_addr.sin_family = AF_INET;
        /* Automatically fill the host's IP(Current PC) */
    serv_addr.sin_addr.s_addr = inet_addr(ip_address);
        /* short integer value for port must be converted into network byte order */
    serv_addr.sin_port = htons(port_no);
        /* Bind returns 0 for success and -1 for error */ 
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        printf("ERROR on binding");
        /* Put the Server to listen mode to fetch th coming requests. Here we keep the maximum size for the backlog queue to 3 */
    listen(sockfd,1);


    //Ckecking for the requests
    clilen = sizeof(cli_addr);
        /* accept() function will write the connecting client's address info into the the address structure */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
        printf("ERROR on accept");

    printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    
    //send a data
    send(newsockfd, "START", 13, 0);
    printf("Sending message: START\n");
    bzero(buffer,256);


    
    //SYN/ASYN and ACK
    n = read(newsockfd,buffer,255);
    if (n < 0)
        printf("ERROR reading from socket");
    printf("Recieved Message: %s\n",buffer);
    if(strcmp(buffer,"INITIATE_SEND")==0){
        printf("Send OK\n");
        send(newsockfd, "OK", 13, 0);
    }



    //Send Image

    FILE *fpread; 
    char dataToBeRead[55], encoded[55]; 
    printf("Enter file name to be sent: ");
    scanf("%s",name);
    scanf("%*c");
    send(newsockfd, name, sizeof(name), 0);
    
    fpread = fopen(name, "rb") ;
      
    if ( fpread == NULL ) 
    { 
        printf( "GfgTest.c file failed to open." ) ; 
    } 
    else
    { 
          
        printf("The file is now opened.\n") ; 
          
        while( fread ( dataToBeRead, sizeof(dataToBeRead),1, fpread ) != NULL ) 
        {  
            encode_nrzi(dataToBeRead,encoded,55);
            send(newsockfd, encoded, sizeof(dataToBeRead), 0);
            n = read(newsockfd,buffer,255);
            if (n < 0)
                break;
            else continue;

         } 
        
        /* int i=0;
        for(;i<10;i++){
            send(newsockfd, "gha", 15, 0);
        } */
          
        fclose(fpread) ; 
        printf("Data successfully sent\n"); 
        printf("The file is now closed.") ; 
    }

    printf("\n\nSending: Close\n");
    send(newsockfd, "CLOSE", 13, 0);


    close(newsockfd);
    close(sockfd);
    return 0; 
}

void encode_nrzi(char *byte, char *encoded, int size){
    int i,j, temp, prev, val;
    for(j = 0;j<size;j++){
        temp=0;
        for(i = 0; i <= 7; i ++){
            
            val = (byte[j] >> i) & 0x01;
            if(i==0){
                prev = val;
                temp = (prev<<i);
            }
            else{
                if(val == 0){
                    temp = temp+(prev<<i);
                }
                if(val == 1){
                    if(prev == 0)
                        prev =1;
                    else
                        prev = 0;
                    temp = temp+(prev<<i);
                }
            }
        }
        encoded[j] = temp;
    }
}

