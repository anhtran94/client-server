#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "protocol.h"
#include "nplaces.h"
#include "things.h"
#define nthings n_thing_place
#include "util.h"

static int port = DEFAULT_PORT;
static int listenfd;
static char hello[100];
static int hellolen;

struct client {
    int fd;
    int id;  /* unique negative integer */
    struct in_addr ipaddr;
    int loc;  /* where this person is */
    char handle[MAXHANDLE + 1];  /* zero-terminated */
    char buf[200];  /* command-line or command-line in progress */
    int bytes_in_buf;  /* how many data bytes already read in buf */
    struct client *next;  /* next item in linked list of clients */
} *clientlist = NULL;


static void parseargs(int argc, char **argv);
static void newclient(int fd, struct sockaddr_in *r);
static void removeclient(struct client *p);
static void describe(struct client *p);
static void do_set_handle(struct client *p, int len);
static void do_inv(struct client *p);
static void do_go(struct client *p, int place);
static void do_get(struct client *p, int id);
static void do_drop(struct client *p, int id);
static void do_poke(struct client *p, int id);
static void do_say(struct client *p);
static void do_something(struct client *p, char *wherenewline);
static void send_arrived(int loc, int thing, struct client *donttell);
static void send_departed(int loc, int thing, struct client *donttell);
static void send_string(int fd, char *s);
static void processSelect(int maxfd, fd_set read_set);
static void createSocket(int port);
static int newConnection(int fd, struct client *p);

int main(int argc, char **argv)
{
	struct client *c;
	fd_set read_set;
	int maxfd;
	
	//get port number:
	parseargs(argc, argv); 
   	//create socket, bind and listen
   	createSocket(port);
	
	while (1) {
		FD_ZERO(&read_set); //initialize the set of fds to be empty set
		FD_SET (listenfd, &read_set); //add the socket just created to set
		maxfd = listenfd; //initialize maxfd
		for (c = clientlist; c ; c = c->next) {
			FD_SET (c->fd, &read_set); //add all clients to read_set
			if (c->fd > maxfd){
				maxfd = c->fd; //update maxfd
			}
		}
		processSelect(maxfd, read_set);
	}      
    return (0);
}
void processSelect(int maxfd, fd_set read_set){ //process 1 client everytime
	struct client* p;
	if ( select(maxfd + 1, &read_set, NULL, NULL, NULL) < 0) {
		perror ("select");
		exit (1);
	}
	for (p = clientlist; p; p = p->next) { 
		if (FD_ISSET(p->fd, &read_set)) {
		    break;
		}
	}
	if (FD_ISSET (listenfd, &read_set)){ 
		newConnection(listenfd, p);
	}	
	if (p) {
		int nbytes = read (p->fd, p->buf, sizeof(p->buf)- p->bytes_in_buf);
		if (nbytes < 0) {
			perror ("read socket");
			exit (1);
		}
		if (nbytes == 0) { //client closes connection
			fflush(stdout);
			removeclient(p);						
		}
		if (nbytes > 0) {
			p->bytes_in_buf += nbytes; //update bytes_in_buf
			char* newline = memnewline(p->buf, p->bytes_in_buf);
			if (newline != NULL) { 				
				do_something(p, newline); 
			}		
		}		
	}				
}

int newConnection(int fd, struct client *p) {

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int accept_fd;

	accept_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
	if ( accept_fd < 0 ) {
		perror("Accept");
		exit(1);
	} else {
		char temp[200];
		newclient(accept_fd, &client_addr);
		sprintf(temp, "%d %d %d\r\n", PROTOCOL_VERSION, NPLACES, n_thing_place);
		write (accept_fd, temp, strlen(temp));
		return (accept_fd); 
	}
}			

void createSocket(int port){

	struct sockaddr_in serv_addr; 
	
	listenfd = socket (AF_INET, SOCK_STREAM, 0); //create socket, -1 is returned if error
	if (listenfd < 0) {  
		perror("socket");
		exit(1);
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	//fill in structure address
   	serv_addr.sin_family = AF_INET;
   	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	serv_addr.sin_port = htons(port);
	//bind
	if ( bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ){
		perror("bind");
		exit(1);
	}
	//listen returns 0 on success and -1 on error
	if ( listen(listenfd, 10)){
		perror ("listen");
		exit (1);
	}
}

static void parseargs(int argc, char **argv)
{
    int c, status = 0;
    while ((c = getopt(argc, argv, "p:")) != EOF) {
        switch (c) {
        case 'p':
            port = atoi(optarg);
            break;
        default:
            status++;
        }
    }
    if (status || optind != argc) {
        fprintf(stderr, "usage: %s [-p port]\n", argv[0]);
        exit(1);
    }
}


static void newclient(int fd, struct sockaddr_in *r)
{
    struct client *p;
    static int lastid = 0;

    printf("connection from %s\n", inet_ntoa(r->sin_addr));

    if (write(fd, hello, hellolen) != hellolen) {
        close(fd);
        printf("%s didn't even listen to the banner!\n",
                inet_ntoa(r->sin_addr));
        return;
    }

    if ((p = malloc(sizeof(struct client))) == NULL) {
        /* very unlikely */
        fprintf(stderr, "out of memory in adding new client!\n");
        close(fd);
        return;
    }
    
    p->fd = fd;
    p->id = --lastid;
    p->ipaddr = r->sin_addr;
    p->bytes_in_buf = 0;
    p->loc = INITIAL_LOC;
    p->handle[0] = '\0';  /* indicates that it hasn't been input yet */
    p->next = clientlist;
    clientlist = p;

}

static void removeclient(struct client *p)
{
    struct client **pp;
    int oldid, oldloc, i;
    char buf[30];

    printf("disconnecting client %s\n", inet_ntoa(p->ipaddr));
    close(p->fd);
    oldid = p->id;
    oldloc = p->loc;

    /* remove */
    for (pp = &clientlist; *pp && *pp != p; pp = &((*pp)->next))
        ;
    if (*pp == NULL) {
        fprintf(stderr, "very odd -- I can't find that client\n");
    } else {
        *pp = (*pp)->next;
        free(p);
    }

    /* drop all possessions */
    for (i = 0; i < nthings; i++) {
        if (thing_place[i] == oldid) {
            thing_place[i] = oldloc;
            send_arrived(oldloc, i, NULL);
        }
    }

    /* tell everyone this person has quit */
    send_departed(oldloc, oldid, NULL);
    sprintf(buf, "quit %d\r\n", oldid);
    for (p = clientlist; p; p = p->next)
        send_string(p->fd, buf);
}


static void describe(struct client *p)
{
    int i;
    char buf[40];
    struct client *q;

    sprintf(buf, "loc %d\r\n", p->loc);
    send_string(p->fd, buf);
    for (i = 0; i < nthings; i++) {
        if (thing_place[i] == p->loc) {
            sprintf(buf, "here %d\r\n", i);
            send_string(p->fd, buf);
        }
    }
    for (q = clientlist; q; q = q->next) {
        if (q != p && q->loc == p->loc) {
            sprintf(buf, "here %d\r\n", q->id);
            send_string(p->fd, buf);
        }
    }
}


static void do_set_handle(struct client *p, int len)
{
    struct client *q;
    char buf[MAXHANDLE + 50];
    int i, c;

    if (len > MAXHANDLE) {
        fprintf(stderr, "handle is %d chars long, max %d\n", len, MAXHANDLE);
        removeclient(p);
        return;
    }

    /* copy characters, check for bad ones */
    for (i = 0; i < len; i++) {
        c = (p->buf[i] & 255);
        if (c < ' ' || (c >= 127 && c < 160)) {
            fprintf(stderr, "handle contains illegal character %d\n", c);
            removeclient(p);
            return;
        }
        p->handle[i] = c;
    }
    p->handle[len] = '\0';

    printf("set handle of fd %d to %s\n", p->fd, p->handle);

    /* tell everyone else about the newcomer */
    sprintf(buf, "name %d %s\r\n", p->id, p->handle);
    for (q = clientlist; q; q = q->next)
        send_string(q->fd, buf);

    /* tell the newcomer about everyone else */
    for (q = clientlist; q; q = q->next) {
        if (q != p) {
            sprintf(buf, "name %d %s\r\n", q->id, q->handle);
            send_string(p->fd, buf);
        }
    }

    /* move the newcomer to the initial location */
    send_arrived(p->loc, p->id, p);
    describe(p);
}


static void do_inv(struct client *p)
{
    int i;
    char buf[30];

    send_string(p->fd, "ib\r\n");
    for (i = 0; i < nthings; i++) {
        if (thing_place[i] == p->id) {
            sprintf(buf, "i %d\r\n", i);
            send_string(p->fd, buf);
        }
    }
    send_string(p->fd, "ie\r\n");
}


static void do_go(struct client *p, int place)
{
    if (place < 0 || place >= NPLACES) {
        fprintf(stderr, "invalid place %d from client fd %d\n", 
                place, p->fd);
        send_string(p->fd, "invalid place number\r\n");
        return;
    }

    send_departed(p->loc, p->id, p);
    p->loc = place;
    send_arrived(p->loc, p->id, p);
    describe(p);
}


static void do_get(struct client *p, int id)
{
    if (id < 0 || id >= nthings) {
        fprintf(stderr, "invalid thing %d from client fd %d\n", 
                id, p->fd);
        send_string(p->fd, "invalid thing number\r\n");
        return;
    }

    if (thing_place[id] != p->loc) {
        send_string(p->fd, "ng\r\n");
        return;
    }

    thing_place[id] = p->id;
    send_departed(p->loc, id, p);
    send_string(p->fd, "ok\r\n");
}


static void do_drop(struct client *p, int id)
{
    if (id < 0 || id >= nthings) {
        fprintf(stderr, "invalid thing %d from client fd %d\n", 
                id, p->fd);
        send_string(p->fd, "invalid thing number\r\n");
        return;
    }

    if (thing_place[id] != p->id) {
        send_string(p->fd, "nd\r\n");
        return;
    }

    thing_place[id] = p->loc;
    send_arrived(p->loc, id, p);
    send_string(p->fd, "ok\r\n");
}


static void do_poke(struct client *p, int id)
{
    char buf[30];
    struct client *q;

    if (id > 0)
        id = -id;

    for (q = clientlist; q && q->id != id; q = q->next)
        ;
    if (!q || p->loc != q->loc) {
        send_string(p->fd, "np\r\n");
        return;
    } else {
        sprintf(buf, "poked %d\r\n", p->id);
        send_string(q->fd, buf);
        send_string(p->fd, "ok\r\n");
    }
}
static void do_say(struct client *p) {
	struct client *i;
	char say_what[80];
	memset(say_what, '\0', sizeof say_what);
	strncpy(say_what, p->buf + 3, p->bytes_in_buf -3);
	//add terminating \0 to the end
	say_what[p->bytes_in_buf -3] = '\0';

	//loop through all clients
	
	for (i = clientlist; i ; i=i->next) {
		if (i->loc == p->loc) {
			char said[100]; 
			memset(said, '\0', sizeof said);
			strcpy(said, "said ");
			char id_str[30];
			memset(id_str, '\0', sizeof id_str);
			//print the whole message to said:
			sprintf(said, "said %d%s\r\n", p->id, say_what);
			send_string(i->fd, said);//send to clients
		}
	}
}

/* there is a command in the buffer; do it */
static void do_something(struct client *p, char *wherenewline)
{
    int len, n;
    len = wherenewline - p->buf;
    *wherenewline = '\0';

    if (len == 0) {
        /* ignore blank lines */
    } else if (p->handle[0] == '\0') {
        do_set_handle(p, len);
    } else if (strcmp(p->buf, "inv") == 0) {
        do_inv(p);
    } else if (strcmp(p->buf, "descr") == 0) {
        describe(p);
    } else if (match_arg(p->buf, "go", &n)) {
        do_go(p, n);
    } else if (match_arg(p->buf, "get", &n)) {
        do_get(p, n);
    } else if (match_arg(p->buf, "drop", &n)) {
        do_drop(p, n);
    } else if (match_arg(p->buf, "poke", &n)) {
        do_poke(p, n);
    } else if (strncmp(p->buf, "say ", 4) == 0) {
		do_say(p);
	} else {
        char buf[100];
        fprintf(stderr, "invalid command from fd %d: %.*s\n", 
                p->fd, len, p->buf);
        sprintf(buf, "error invalid: %.*s\r\n", len, p->buf);
        send_string(p->fd, buf);
    }

    /* p->buf[len] was either \r or \n.  How about p->buf[len+1]? */
    len++;
    if (len > p->bytes_in_buf && (p->buf[len] == '\r' || p->buf[len] == '\n'))
        len++;
    p->bytes_in_buf -= len;
    memmove(p->buf, p->buf + len, p->bytes_in_buf);
}


static void send_arrived(int loc, int thing, struct client *donttell)
{
    struct client *q, *n;
    for (q = clientlist; q; q = n) {
        n = q->next;
        if (q != donttell && q->loc == loc) {
            char buf[100];
            sprintf(buf, "arr %d\r\n", thing);
            send_string(q->fd, buf);
			
        }
    }
}


static void send_departed(int loc, int thing, struct client *donttell)
{
    struct client *q, *n;
    for (q = clientlist; q; q = n) {
        n = q->next;
        if (q != donttell && q->loc == loc) {
            char buf[100];
            sprintf(buf, "dep %d\r\n", thing);
            send_string(q->fd, buf);
        }
    }
}


static void send_string(int fd, char *s)
{
    int len = strlen(s);
    if (write(fd, s, len) != len)
        perror("write");
}
