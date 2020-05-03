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
#include <string.h>
#include<iostream>
#include<string>
using namespace std;

void decode_nrzi(char*,char*,int);
void decode_manchester(char*,char*,int);
void decode_diff_manchester(char*,char*,int);

string convertToString(char* a, int size) 
{ 
    string s = a; 
    return s; 
} 

int main()
{
    int sockfd, port_no, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256], ip_address[20], port_char[10], password[20];
    
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
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port_no);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        printf("ERROR connecting");

    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0) 
         printf("ERROR reading from socket");

    goto password_recieve;

    password_recieve:{
        printf("\nPlease enter the password: ");
        scanf("%s",password);
        scanf("%*c");
    }

    if(strcmp(password,buffer)){
        printf("Incorrect password.......!!!!!\n");
        goto password_recieve;
    }

    printf("Connection Seccessfull\n");

    printf("\nSending: SYN\n");
    send(sockfd, "SYN", 4, 0);

    n = read(sockfd, buffer, 255);
    if (n < 0) 
         printf("ERROR reading from socket");
    printf("Message Recieved: %s\n", buffer);

    if(strcmp(buffer,"SYN_ACK")==0)
    {
        char buf[] = "ACK";
        printf("Sending: ACK\n");
        send(sockfd, buf, strlen(buf), 0);

    }
    n = read(sockfd, buffer, 255);
    if (n < 0) 
         printf("ERROR reading from socket");


    
    FILE *fpwrite ; 
    char name[30];
    
    while(1){
        n = read(sockfd, buffer, sizeof(buffer));
        send(sockfd, "1", 10, 0);
        if(strcmp(buffer,"1")==0){
            n = read(sockfd, buffer, sizeof(buffer));
            send(sockfd, "1", 10, 0);
            
            //Read image 
            n = read(sockfd, name, sizeof(name));
            printf("Recieving file %s from server\nEnter the name with path and extension to save the file: ",name);
            scanf("%s",name);
            scanf("%*c");
            //fpwrite = fopen(dataToBeRead, "wb") ; 
            fpwrite = fopen(name,"wb");
            
            if ( fpwrite == NULL ) 
            { 
                printf( "File failed to open." ) ; 
            } 
            else{
                if(strcmp(buffer,"1")==0){
                    char dataToBeRead[50], decoded[50];
                    send(sockfd, "SYN", 4, 0);
                    printf("\nData transfer started....!!!\nUsing NRZ-I encoding\n");
                    n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
                    decode_nrzi(dataToBeRead,decoded,50);
                    while(strcmp(dataToBeRead,"COMPLETE")){
                        send(sockfd, "1", strlen("1"), 0);
                        decode_nrzi(dataToBeRead,decoded,50);
                        fwrite(decoded,1,sizeof(decoded),fpwrite);
                        n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
                    }
                }
                else if(strcmp(buffer,"2")==0){
                    char dataToBeRead[50], decoded[50];
                    send(sockfd, "SYN", 4, 0);
                    printf("\nData transfer started....!!!\nUsing Manchester Encoding\n");
                    n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
                    decode_nrzi(dataToBeRead,decoded,50);
                    while(strcmp(dataToBeRead,"COMPLETE")){
                        send(sockfd, "1", strlen("1"), 0);
                        decode_nrzi(dataToBeRead,decoded,50);
                        fwrite(decoded,1,sizeof(decoded),fpwrite);
                        n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
                    }
                }
                else if(strcmp(buffer,"3")==0){
                    char dataToBeRead[50], decoded[50];
                    send(sockfd, "SYN", 4, 0);
                    printf("\nData transfer started....!!!\nUsing Differential Manchester encoding\n");
                    n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
                    decode_nrzi(dataToBeRead,decoded,50);
                    while(strcmp(dataToBeRead,"COMPLETE")){
                        send(sockfd, "1", strlen("1"), 0);
                        decode_nrzi(dataToBeRead,decoded,50);
                        fwrite(decoded,1,sizeof(decoded),fpwrite);
                        n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
                    }
                }
                printf("Data transfer completed.....!!\nClosing file now...!!!\n");

                fclose(fpwrite);
            }
        }
        else if(strcmp(buffer,"2")==0){
            int z=1;
            char dataToBeRead[50];
            n = read(sockfd, dataToBeRead, sizeof(dataToBeRead));
            printf("message recieved: %s\n",dataToBeRead);
            string msg = convertToString(dataToBeRead, strlen(dataToBeRead));
            string encode="",crc;
            cout<<"Enter the CRC generator polynomial "<<endl;
            getline(cin,crc);
            int m = msg.length();
            int n =crc.length();
            
            encode+=msg; 

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
            for(int i= encode.length()-(n-1);i<encode.length();i++)
            {
                if(encode[i]!= '0')
                {
                    cout<<"Error detected"<<endl;
                    z=0;
                    break;
                    
                }
            }
            if(z)
                cout<<"No Error detected"<<endl;


        }
        else if(strcmp(buffer,"3")==0){
            printf("\nClosing Socket\n");
            close(sockfd);
            return 0;
        }
        

    } 

    
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

void decode_manchester(char *encoded, char *decoded, int size){
    int i,j,val,prev,temp,k;
    for(j = 0;j<size;j+=2){
        temp=0;
        for(i = 0; i <= 15; i+=2){
            
            if(i<8){
                val = (encoded[j] >> i) & 0x01;
                
                if(val == 0){
                    temp = temp+(1<<(i/2));
                }
                else{
                    temp = temp+(0<<(i/2));
                }
            }
            else{
                k=i-8;
                val = (encoded[j+1] >> k) & 0x01;
                
                if(val == 0){
                    temp = temp+(1<<(i/2));
                }
                else{
                    temp = temp+(0<<(i/2));
                }
            }
        }
        decoded[j/2] = temp;
    }
}

void decode_diff_manchester(char *encoded, char *decoded, int size){
    int i,j,val,prev = 0,temp,k;
    for(j = 0;j<size;j+=2){
        temp=0;
        for(i = 0; i <= 15; i+=2){
            
            if(i<8){
                val = (encoded[j] >> i) & 0x01;
                if(prev == 0){
                    if(val == 0){
                        temp = temp+(1<<(i/2));
                    }
                    else{
                        temp = temp+(0<<(i/2));
                        prev = 1;
                    }
                }
                else{
                    if(val == 0){
                        temp = temp+(0<<(i/2));
                        prev = 0;
                    }
                    else{
                        temp = temp+(1<<(i/2));
                    }
                }
            }
            else{
                k=i-8;
                val = (encoded[j+1] >> k) & 0x01;
                if(prev == 0){
                    if(val == 0){
                        temp = temp+(1<<(i/2));
                    }
                    else{
                        temp = temp+(0<<(i/2));
                        prev = 1;
                    }
                }
                else{
                    if(val == 0){
                        temp = temp+(0<<(i/2));
                        prev = 0;
                    }
                    else{
                        temp = temp+(1<<(i/2));
                    }
                }
            }
        }
        decoded[j/2] = temp;
    }
}