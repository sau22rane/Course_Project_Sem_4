#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include<iostream>
#include<string>
using namespace std;

void encode_nrzi(char*,char*,int);
void encode_manchester(char*,char*,int);
void encode_diff_manchester(char*,char*,int);

int main(){
    int sockfd, newsockfd, port_no, n;
    socklen_t clilen;
    char buffer[256];
    int opt = 1;
    char ip_address[20], password[20], name[20];
    struct sockaddr_in serv_addr, cli_addr;
    /* if (argc < 2) {
        printf("ERROR, no port provided\n");
        exit(1);
    } */

    printf("Enter the IP address of this PC: ");
    scanf("%s",ip_address);
    printf("Enter the port number: ");
    scanf("%d",&port_no);
    printf("Create a password for server: ");
    scanf("%s",password);
    scanf("%*c");
    printf("Setting up server\nWaiting for Connections\n\n");

    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        printf("ERROR opening socket");

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

    
    //send a data
    send(newsockfd, password, strlen(password), 0);
    
    n = read(newsockfd,buffer,255);
    if (n < 0)
        printf("ERROR reading from socket");
    printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    printf("Recieved Message: %s\n",buffer);


    if(strcmp(buffer,"SYN")==0){
        printf("Sending SYN_ACK\n");
        send(newsockfd, "SYN_ACK", 13, 0);
    }

    
    bzero(buffer,256);


     
    //SYN/ASYN and ACK
    n = read(newsockfd,buffer,255);
    if (n < 0)
        printf("ERROR reading from socket");
    printf("Recieved Message: %s\n",buffer);

    if(strcmp(buffer,"ACK")==0){
        send(newsockfd, "OK", 13, 0);
    }
//------------------------------------------------------------------------------------------

    int choice, encoding;
    char encoded[50], dataToBeRead[50],man_data[25];
    while(1){
        printf("\n\nSelect one of the following option:\n1. Send data\n2. Demonstrate CRC\n3. close connection\nYour choice: ");
        scanf("%d",&choice);
        scanf("%*c");
        switch(choice){
            case 1:
                //Send Image
                send(newsockfd, "1", 11, 0);
                n = read(sockfd, buffer, sizeof(buffer));
                printf("\nSelect one of the following encoding:\n1. NRZ-I\n2. Manchester\n3. Differential Manchester\nYour choice: ");
                scanf("%d",&encoding);
                scanf("%*c");
                FILE *fpread;
                switch(encoding){
                    case 1:
                    //NRZ-I encoding
                    send(newsockfd, "1", 10, 0);
                    n = read(sockfd, buffer, sizeof(buffer));
                    printf("\nEnter file name to be sent: ");
                    scanf("%s",name);
                    scanf("%*c");
                    send(newsockfd, name, sizeof(name), 0);
                    
                    fpread = fopen(name, "rb") ;
                    
                    if ( fpread == NULL ) 
                    { 
                        printf( "%s failed to open.\n",name) ; 
                    } 
                    else
                    { 
                        
                        printf("\nThe file is now opened...\nStarting Data transfer now....!!!!\n");
                        n = read(newsockfd,buffer,255);
                        if (n < 0)
                            printf("ERROR reading from socket");
                        
                        while( fread ( dataToBeRead, sizeof(dataToBeRead),1, fpread ) != NULL ) 
                        {  
                            encode_nrzi(dataToBeRead,encoded,50);
                            send(newsockfd, encoded, sizeof(encoded), 0);
                            n = read(newsockfd,buffer,255);
                            if (n < 0)
                                break;
                            else continue;

                        } 
                        
                        fclose(fpread) ; 
                        printf("Data successfully sent\n"); 
                        send(newsockfd, "COMPLETE", 13, 0);
                        
                    }
                    break;
                case 2:
                    //encode_manchester
                    send(newsockfd, "2", 10, 0);
                    n = read(sockfd, buffer, sizeof(buffer));
                    printf("\nEnter file name to be sent: ");
                    scanf("%s",name);
                    scanf("%*c");
                    send(newsockfd, name, sizeof(name), 0);
                    
                    fpread = fopen(name, "rb") ;
                    
                    if ( fpread == NULL ) 
                    { 
                        printf( "%s failed to open.\n",name) ; 
                    } 
                    else
                    { 
                        
                        printf("\nThe file is now opened...\nStarting Data transfer now....!!!!\n");
                        n = read(newsockfd,buffer,255);
                        if (n < 0)
                            printf("ERROR reading from socket");
                        
                        while( fread ( dataToBeRead, sizeof(dataToBeRead),1, fpread ) != NULL ) 
                        {  
                            encode_nrzi(dataToBeRead,encoded,50);
                            send(newsockfd, encoded, sizeof(encoded), 0);
                            n = read(newsockfd,buffer,255);
                            if (n < 0)
                                break;
                            else continue;

                        } 
                        
                        fclose(fpread) ; 
                        printf("Data successfully sent\n"); 
                        send(newsockfd, "COMPLETE", 13, 0);
                        
                    }
                    break;
                case 3:
                    //encode_diff_manchester
                    send(newsockfd, "3", 10, 0);
                    n = read(sockfd, buffer, sizeof(buffer));
                    printf("\nEnter file name to be sent: ");
                    scanf("%s",name);
                    scanf("%*c");
                    send(newsockfd, name, sizeof(name), 0);
                    
                    fpread = fopen(name, "rb") ;
                    
                    if ( fpread == NULL ) 
                    { 
                        printf( "%s failed to open.\n",name) ; 
                    } 
                    else
                    { 
                        
                        printf("\nThe file is now opened...\nStarting Data transfer now....!!!!\n");
                        n = read(newsockfd,buffer,255);
                        if (n < 0)
                            printf("ERROR reading from socket");
                        
                        while( fread ( dataToBeRead, sizeof(dataToBeRead),1, fpread ) != NULL ) 
                        {  
                            encode_nrzi(dataToBeRead,encoded,50);
                            send(newsockfd, encoded, sizeof(encoded), 0);
                            n = read(newsockfd,buffer,255);
                            if (n < 0)
                                break;
                            else continue;

                        } 
                        
                        fclose(fpread) ; 
                        printf("Data successfully sent\n"); 
                        send(newsockfd, "COMPLETE", 13, 0);
                        
                    }
                    break;
                }
                break;

            case 2:
                //Demonstrate crc
                {
                    send(newsockfd, "2", 13, 0);
                int cz;
                printf("Select one of the following alternative\n1. Send a message\n2. Tamper message\nYour selection: ");
                scanf("%d",&cz);
                scanf("%*c");

                string msg, crc, encode = "";
                cout<<"Enter a message"<<endl;
                getline(cin,msg);
                cout<<"Enter the CRC generator polynomial "<<endl;
                getline(cin,crc);
                int m = msg.length();
                n =crc.length();
                encode+=msg;
                for(int i=0;i<n-1;i++)
                    encode+='0';   

                for (int i=0 ;i<=encode.length()-n;)  // stop when we complete all the message bits
                {
                    for(int j=0;j<n;j++)
                    {
                        if(encode[i+j]==crc[j])  // condition for 1 XOR 1 or 0 XOR 0
                            encode[i+j] = '0';
                        else
                            encode[i+j] = '1';
                    }
                    
                    for(;i<encode.length() && encode[i]!='1';i++) ; // remainder 1 not 0 
                        
                    
                }
                for(int i= encode.length()-(n-1);i<encode.length();i++){
                    msg+=encode[i];
                }
                cout<<endl<<"Sending message: "<<msg<<endl;
                cout<<endl;
                strcpy(dataToBeRead,msg.c_str());
                switch(cz){

                    case 1:
                        send(newsockfd, dataToBeRead, sizeof(dataToBeRead), 0);
                        break;
                    case 2:

                        encode_nrzi(dataToBeRead,encoded,50);
                        send(newsockfd, encoded, sizeof(encoded), 0);
                        break;

                }
                break;
                }

            case 3:
                send(newsockfd, "3", 13, 0);
                close(newsockfd);
                close(sockfd);
                return 0; 
        }
    }

    /* printf("\n\nShutting down server\n");
    send(newsockfd, "CLOSE", 13, 0); */


    
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

void encode_manchester(char *byte, char *encoded, int size){
    int i,j, temp1, temp2, prev, val,k;
    for(j = 0;j<size;j++){
        temp1=0;
        temp2 = 0;
        for(i = 0; i <= 7; i ++){
            
            val = (byte[j] >> i) & 0x01;
            if(i<4){
                if(val == 0){
                    temp1 = temp1+(1<<(i*2));
                    temp1 = temp1+(0<<(i*2+1));
                }
                if(val == 1){
                    temp1 = temp1+(0<<(i*2));
                    temp1 = temp1+(1<<(i*2+1));             
                }
            }
            else{
                k = i-4;
                if(val == 0){
                    temp2 = temp2+(1<<(k*2));
                    temp2 = temp2+(0<<(k*2+1));
                }
                if(val == 1){
                    temp2 = temp2+(0<<(k*2));
                    temp2 = temp2+(1<<(k*2+1));            
                }
            }
        }
        encoded[j*2] = temp1;
        encoded[j*2+1] = temp2;
    }
}

void encode_diff_manchester(char *byte, char *encoded, int size){
    int i,j, temp1, temp2, prev = 0, val,k;
    for(j = 0;j<size;j++){
        temp1=0;
        temp2 = 0;
        for(i = 0; i <= 7; i ++){
            
            val = (byte[j] >> i) & 0x01;
            if(i<4){
                if(prev == 1){
                    if(val == 0){
                        temp1 = temp1+(0<<(i*2));
                        temp1 = temp1+(1<<(i*2+1));
                        prev = 0;
                    }
                    if(val == 1){
                        temp1 = temp1+(1<<(i*2));
                        temp1 = temp1+(0<<(i*2+1));               
                    }
                }
                else{
                    if(val == 0){
                        temp1 = temp1+(1<<(i*2));
                        temp1 = temp1+(0<<(i*2+1));
                        prev = 1;
                    }
                    if(val == 1){
                        temp1 = temp1+(0<<(i*2));
                        temp1 = temp1+(1<<(i*2+1));           
                    }
                }
            }
            else{
                k = i-4;
                if(prev == 1){
                    if(val == 0){
                        temp2 = temp2+(0<<(k*2));
                        temp2 = temp2+(1<<(k*2+1));
                        prev = 0;
                    }
                    if(val == 1){
                        temp2 = temp2+(1<<(k*2));
                        temp2 = temp2+(0<<(k*2+1));           
                    }
                }
                else{
                    if(val == 0){
                        temp2 = temp2+(1<<(k*2));
                        temp2 = temp2+(0<<(k*2+1));
                        prev = 1;
                    }
                    if(val == 1){
                        temp2 = temp2+(0<<(k*2));
                        temp2 = temp2+(1<<(k*2+1));        
                    }
                }
            }
        }
        encoded[j*2] = temp1;
        encoded[j*2+1] = temp2;
    }
}