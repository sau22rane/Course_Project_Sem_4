#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

main(int argc, char *argv[]){
    int sockfd, newsockfd, port_no, n;
    socklen_t clilen;
    char buffer[256];
    int opt = 1;
    struct sockaddr_in serv_addr, cli_addr;
    if (argc < 2) {
        printf("ERROR, no port provided\n");
        exit(1);
    }
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
    port_no = atoi(argv[1]);
        /* AF_INET      		IPv4 Internet protocols  */
    serv_addr.sin_family = AF_INET;
        /* Automatically fill the host's IP(Current PC) */
    serv_addr.sin_addr.s_addr = INADDR_ANY;
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
    send(newsockfd, "Hello, world!\n", 13, 0);
    printf("Sending message: Hello, World\n");
    bzero(buffer,256);

    //Read a data
    n = read(newsockfd,buffer,255);
    if (n < 0)
        printf("ERROR reading from socket");
    printf("Recieved Message: %s\n",buffer);

    close(newsockfd);
    close(sockfd);
    return 0; 
}



