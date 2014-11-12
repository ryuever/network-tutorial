/* TCPecho.c - main, TCPecho */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int	TCPecho(const char *host, const char *service, const char *path);
int	errexit(const char *format, ...);
int	connectTCP(const char *host, const char *service);

#define	LINELEN		128
#define LINELEN2    1000000
/*------------------------------------------------------------------------
 * main - TCP client for ECHO service
 * ./Tcpecho1 150.65.118.70 80 /picture/reiachan.png
 * open temp.png
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	char	*host = "localhost";	/* host to use if none supplied	*/
	char	*service = "echo";	/* default service name		*/
    char *path = NULL;
    
	switch (argc) {
	case 1:
		host = "localhost";
		break;
    case 4:
        path = argv[3];
	case 3:
		service = argv[2];
		/* FALL THROUGH */
	case 2:
		host = argv[1];
		break;
	default:
		fprintf(stderr, "usage: TCPecho [host [port]]\n");
		exit(1);
	}
	TCPecho(host, service, path);
	exit(0);
}

/*------------------------------------------------------------------------
 * TCPecho - send input to ECHO service on specified host and print reply
 *------------------------------------------------------------------------
 */
int
TCPecho(const char *host, const char *service, const char *path)
{
	char	buf[LINELEN2+1];		/* buffer for one line of text	*/
    char request[150] = "";
    snprintf(request, sizeof request, "%s%s%s","GET ",path," HTTP/1.0\r\n\r\n");
    /* snprintf(request, sizeof request, "%s%s%s","GET /member/himrock922/",path," HTTP/1.0"); */
    size_t requestlen;
	int	s, n;			/* socket descriptor, read count*/
	int	outchars, inchars;	/* characters sent and received	*/
    FILE *fp;

	s = connectTCP(host, service);
    requestlen = strlen(request);
    int byte_count = 0,ret;
    /* (read(fd, buffer + byte_count, http_buffer_size - byte_count) > 0) */

    int b = write(s, request,requestlen);
    /* printf("read size is %d\n",b); */

    /* printf("c is %d", c); */
    /* fputs(buf, stdout); */

    if((fp = fopen("temp.png", "w")) == NULL )
        printf("file can not be open\n");

    while((ret = read(s, buf+byte_count, LINELEN2 - byte_count)) > 0){
        byte_count += ret;
        printf("byte_count is %d %d\n",byte_count, ret);
    }

    int hrd;
    hrd = truncateHeader(buf, byte_count);
    printf("count is %d\n", hrd);
    fwrite(buf+hrd,byte_count-hrd, 1, fp);
    fclose(fp);
}

int truncateHeader(const char *buf, int byte_count){
    int i = 0;
    for (i=0; i<byte_count; i++){
        if (buf[i] == '\r' && buf[i+1] == '\n' && buf[i+2] == '\r' && buf[i+3] == '\n'){
            return i+4;
        }
    } 
}
