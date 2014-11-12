INCLUDE =
CC = clang 
CFLAGS = -g

CLIENTS = hostname_to_ip_getaddrinfo hostname_to_ip_gethostbyname
SERVERS = 

CLIENTOBJ = hostname_to_ip_getaddrinfo.o hostname_to_ip_gethostbyname.o

all: ${CLIENTS}
.SECONDEXPANSION:
$(CLIENTS): $$@.c
	$(CC) $(CFLAGS) -o $@ $@.c

$(SERVERS): $$@.c
	$(CC) $(CFLAGS) -o $@ $@.c

clean :
	rm -f ${CLIENTS} ${SEREVERS} a.out
