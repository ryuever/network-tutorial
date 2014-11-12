#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //for exit(0);
#include<sys/socket.h>
#include<errno.h> //For errno - the error number
#include<netdb.h> //hostent
#include<arpa/inet.h>
#define h_addr h_addr_list[0] 

int hostname_to_ip(char *  , char *);
 
int main(int argc , char *argv[])
{
    if(argc <2)
    {
        printf("Please provide a hostname to resolve");
        exit(1);
    }
     
    char *hostname = argv[1];
    char ip[100];

    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( hostname ) ) == NULL) 
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    printf("official name is %s\n\n", he->h_name);
    printf("hostname aliases :\n");
    for(i=0; he->h_aliases[i]; i++){
        printf("%s\n",he->h_aliases[i]);
    }
    printf("\n");
 
    printf("address length is %d\n\n", he->h_length);
    printf("address type is %d\n\n", he->h_addrtype);

    addr_list = (struct in_addr **) he->h_addr_list;
     
    printf("resolved ip address :\n");
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        printf("ip[%d] is %s\n", i, ip);
        /* return 0; */
    }
}
