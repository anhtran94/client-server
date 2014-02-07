#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "protocol.h"
#include "mud.h"
#include "lang.h"
#include "map.h"
#include "things.h"
#include "util.h"

static char *host = "localhost";
static int port = DEFAULT_PORT;

int serverfd;
char buf[200];  /* communication from server */
int bytes_in_buf = 0;
int mylocation;

int saw_inventory_something;


static struct namelist {
    char *name;
    int id;
    struct namelist *next;
} *names = NULL;


static void parseargs(int argc, char **argv);
static void connect_to_server();
static void gethandle();
static void do_something();
static void do_something_server(char *wherenewline);
static void docmd(char **cmd);
static void call_with_arg(void (*f)(int), char *arg, char *expln, char *cmdname);
static void get(int obj);
static void drop(int obj);
static void poke(int obj);
static void go(int dir);
static void help();
static void loc(int place);
static void here(int id);
static void arrived(int id);
static void departed(int id);
static void pokedby(int id);
static void startup_checks();
static void storename(int id, char *name);
static void removename(int id);
static char *find_name(int id);
static char **explode(char *s);
static int parsenumber(char *s);
static char *say_what(char *buf, int name_len);
static int find_id_len(char* buf);

int main(int argc, char **argv)
{
    startup_checks();
    parseargs(argc, argv);
    connect_to_server();
    gethandle();
    while (1)
	do_something();
}


static void parseargs(int argc, char **argv)
{
    int status = 0;
    if (argc > 1)
	host = argv[1];
    if (argc > 2)
	if ((port = atoi(argv[2])) < 0)
	    status = 1;
    if (argc > 3 || status) {
	fprintf(stderr, "usage: %s [hostname [portnum]]\n", argv[0]);
	exit(1);
    }
}


static void connect_to_server()
{
    struct hostent *hp;
    struct sockaddr_in r;
    char *q;
    int len, server_protocol, server_nplaces, server_nthings;

    if ((hp = gethostbyname(host)) == NULL) {
	fprintf(stderr, "%s: no such host\n", host);
	exit(1);
    }
    if (hp->h_addr_list[0] == NULL || hp->h_addrtype != AF_INET) {
	fprintf(stderr, "%s: not an internet protocol host name\n", host);
	exit(1);
    }

    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    memset((char *)&r, '\0', sizeof r);
    r.sin_family = AF_INET;
    memcpy((char *)&r.sin_addr, hp->h_addr_list[0], hp->h_length);
    r.sin_port = htons(port);

    if (connect(serverfd, (struct sockaddr *)&r, sizeof r) < 0) {
        perror("connect");
        exit(1);
    }

    /* read banner line */
    while (!(q = memnewline(buf, bytes_in_buf))) {
	if ((len = read(serverfd, buf+bytes_in_buf, sizeof buf - bytes_in_buf))
		== 0) {
	    printf("server dropped the connection\n");
	    exit(0);
	} else if (len < 0) {
	    perror("read");
	    exit(1);
	}
	bytes_in_buf += len;
    }

    *q = '\0';
    if (sscanf(buf, "%d%d%d",
		    &server_protocol, &server_nplaces, &server_nthings)
	    != 3) {
	fprintf(stderr, "can't parse server banner line\n");
	exit(0);
    }
    if (server_protocol != PROTOCOL_VERSION) {
	fprintf(stderr, "protocol version mismatch\n");
	exit(0);
    }
    if (server_nplaces != nplaces || server_nthings != lang_nthings) {
	fprintf(stderr, "server has a different map than we do\n");
	exit(0);
    }

    /* remove the banner line from the already-read buffer */
    len = q - buf + 1;
    if (bytes_in_buf > len && (buf[len] == '\r' || buf[len] == '\n'))
	len++;
    bytes_in_buf -= len;
    memmove(buf, buf + len, bytes_in_buf);
}


static void send_string(char *s)
{
    int len = strlen(s);
    if (write(serverfd, s, len) != len)
	perror("write");
}


static void gethandle()
{
    char buf[MAXHANDLE + 3], *p;
    do {
	printf("%s: ", lang_handle_request);
	if (fgets(buf, MAXHANDLE+1, stdin) == NULL)
	    exit(0);
	if ((p = strchr(buf, '\n')))
	    *p = '\0';
    } while (buf[0] == '\0');
    strcat(buf, "\r\n");
    send_string(buf);
}


static void do_something()
{
    char *q;

    if ((q = memnewline(buf, bytes_in_buf))) {
	do_something_server(q);
    } else {
	fd_set fdlist;
	FD_ZERO(&fdlist);
	FD_SET(0, &fdlist);
	FD_SET(serverfd, &fdlist);
	if (select(serverfd+1, &fdlist, NULL, NULL, NULL) < 0) {
	    perror("select");
	} else {
	    if (FD_ISSET(serverfd, &fdlist)) {
		int n = read(serverfd, buf+bytes_in_buf, sizeof buf - bytes_in_buf);
		if (n == 0) {
		    printf("\nserver dropped the connection\n");
		    exit(0);
		} else if (n < 0) {
		    perror("read");
		    exit(1);
		} else {
		    bytes_in_buf += n;
		    if ((q = memnewline(buf, bytes_in_buf)))
			do_something_server(q);
		}
	    }
	    if (FD_ISSET(0, &fdlist)) { //read signal from stdin
		char buf_stdin[80];
		
		if (fgets(buf_stdin, sizeof buf_stdin, stdin) == NULL)
		    exit(0);
		//we are going to compare "say ", or "dire ", so append the space to lang_say:
		char lang_say_space[20];
		strcpy(lang_say_space, lang_say);
		strcat(lang_say_space, " ");
		int lang_say_len = (int) strlen(lang_say);
		if (!strncmp(buf_stdin, lang_say_space, (lang_say_len + 1))) {

			//send command "say text" to server
			char say_command[90];
			char text[80];
			strcpy(say_command, "say");
			strcpy(text, (buf_stdin + lang_say_len));
			strcat(say_command, text);
			strcat(say_command, "\r\n");
			send_string(say_command);
			
		} else {
			docmd(explode(buf_stdin));
		}
	    }
	}
    }
}
int space_1, space_2;
static int find_id_len (char* buf){
	//find the length between 2 spaces
	char* temp = buf;
	int count = 0;
	int size = strlen(buf);
	int flag = 0;
	for (; size > 0 ; temp++) {
		if (*temp == ' ') {
			if (flag == 0) {
				space_1 = count;	
				flag = 1;
			} else {
				space_2 = count;
				break;
			}
		}
		size--;
		count++;
	}
	return (space_2 - space_1 -1);
}

static char* say_what(char* buf, int id_len){
	
	char* text = malloc(strlen(buf));
        buf += (5+ id_len) ; //skip 'said[space] name' 
	strcpy(text, buf); //copy everything from there
        return (text);
}

static void do_something_server(char *wherenewline)
{
    int n;
    *wherenewline = '\0';
    if (match_arg(buf, "loc", &n)) {
		loc(n);
    } else if (match_arg(buf, "here", &n)) {
		here(n);
    } else if (match_arg(buf, "arr", &n)) {
		arrived(n);
    } else if (match_arg(buf, "dep", &n)) {
		departed(n);
    } else if (match_arg(buf, "poked", &n)) {
		pokedby(n);
    } else if (strcmp(buf, "ib") == 0) {
		saw_inventory_something = 0;
		printf("%s\n", lang_inv_heading);
    } else if (match_arg(buf, "i", &n)) {
		saw_inventory_something = 1;
		printf("    %s (#%d)\n", lang_thing[n], n);
    } else if (strcmp(buf, "ie") == 0) {
		if (!saw_inventory_something)
	    printf("%s\n", lang_inv_nothing);
    } else if (strcmp(buf, "ok") == 0) {
		printf("%s\n", lang_ok);
    } else if (strcmp(buf, "ng") == 0) {
		printf("%s\n", lang_get_nosuch);
    } else if (strcmp(buf, "nd") == 0) {
		printf("%s\n", lang_drop_nosuch);
    } else if (strcmp(buf, "np") == 0) {
		printf("%s\n", lang_get_nosuch);
    } else if (strncmp(buf, "said", 4) == 0) {
		char final_say[100];
		int id_len = find_id_len(buf);
		//extract id:
		char id_str[id_len + 1];
		strncpy(id_str, (buf+5), id_len);
		id_str[id_len]= '\0';
		//convert to name:
		int id = atoi(id_str); 
		char *name = find_name(id);
		//extract text:
		char* text = say_what(buf, id_len);	
	 	strcpy(final_say, lang_says_format); // "%s says:"
		strcat(final_say, text); // "%s says: text"	
		printf(final_say, name);
		printf("\n");
		free (text);

	} else if (match_arg(buf, "name", &n)) {
		char *p;
		if ((p = strchr(buf, ' ')) == NULL
			|| (p = strchr(p + 1, ' ')) == NULL)
			fprintf(stderr, "error: malformed 'name' from server\n");
		else
	    	storename(n, p + 1);
    } else if (match_arg(buf, "quit", &n)) {
	removename(n);
    } else if (strncmp(buf, "error ", 6) == 0) {
	printf("error from server: %s\n", buf + 6);
    } else {
	fprintf(stderr, "unexpected data from server: %s\n", buf);
    }

    n = wherenewline - buf;
    n++;
    if (bytes_in_buf > n && (buf[n] == '\r' || buf[n] == '\n'))
	n++;
    bytes_in_buf -= n;
    memmove(buf, buf + n, bytes_in_buf);
}


static void docmd(char **cmd)
{
    int i;

    if (cmd[0] == NULL) {
	help();
	return;
    }
    if (cmd[1] && cmd[2]) {
	printf("%s\n", lang_toolong);
	help();
	return;
    }

    if (strcmp(cmd[0], lang_look[0]) == 0
	    || strcmp(cmd[0], lang_look[1]) == 0) {
	send_string("descr\r\n");
	return;
    }
    if (strcmp(cmd[0], lang_inv[0]) == 0
	    || strcmp(cmd[0], lang_inv[1]) == 0) {
	send_string("inv\r\n");
	return;
    }
    if (strcmp(cmd[0], lang_get) == 0) {
	call_with_arg(get, cmd[1], lang_getdrop_explain, lang_get);
	return;
    }
    if (strcmp(cmd[0], lang_drop) == 0) {
	call_with_arg(drop, cmd[1], lang_getdrop_explain, lang_drop);
	return;
    }
    if (strcmp(cmd[0], lang_poke) == 0) {
	if (cmd[1] && cmd[1][0] == '-')
	    cmd[1]++;
	call_with_arg(poke, cmd[1], lang_poke_explain, lang_poke);
	return;
    }

    for (i = 0; i < 6; i++) {
	if (strcmp(cmd[0], lang_directions[i][0]) == 0
		|| strcmp(cmd[0], lang_directions[i][1]) == 0) {
	    go(i);
	    return;
	}
    }

    /* accept standard command "l" in any language, unless it is assigned
     * another meaning */
    if (strcmp(cmd[0], "l") == 0) {
	send_string("descr\r\n");
	return;
    }

    printf("%s\n", lang_huh);
    help();
}


static void call_with_arg(void (*f)(int), char *arg, char *expln, char *cmdname)
{
    int argnum;
    if (arg == NULL)
	printf(expln, cmdname);
    else if ((argnum = parsenumber(arg)) >= 0)
	(*f)(argnum);
}


static void get(int obj)
{
    if (obj >= 0 && obj < n_thing_place) {
	char buf[40];
	sprintf(buf, "get %d\r\n", obj);
	send_string(buf);
    } else {
	printf("%s\n", lang_get_nosuch);
    }
}


static void drop(int obj)
{
    if (obj >= 0 && obj < n_thing_place) {
	char buf[40];
	sprintf(buf, "drop %d\r\n", obj);
	send_string(buf);
    } else {
	printf("%s\n", lang_drop_nosuch);
    }
}


static void poke(int obj)
{
    char buf[40];
    sprintf(buf, "poke %d\r\n", obj);
    send_string(buf);
}



static void go(int dir)
{
    if (places[mylocation].exit_loc[dir] >= 0) {
	char buf[30];
	sprintf(buf, "go %d\r\n", places[mylocation].exit_loc[dir]);
	send_string(buf);
    } else {
	printf("%s\n", lang_nosuchexit);
    }
}


static void help()
{
    int i;
    printf("%s %s %s %s %s %s", lang_commandlist, lang_get, lang_drop, lang_poke, lang_inv[0], lang_say);
    for (i = 0; i < 6; i++)
	printf(" %s", lang_directions[i][0]);
    printf("\n");
}


static void loc(int place)
{
    int i;
    mylocation = place;
    printf("\n%s %s.\n", lang_youat, lang_place_title[place]);
    if (lang_place_detail[place])
	printf("%s\n", lang_place_detail[place]);
    printf("%s:\n", lang_youcango);
    for (i = 0; i < NDIRECTIONS; i++)
	if (places[place].exit_loc[i] >= 0)
	    printf("    %s %s: %s\n", lang_directions[i][0], lang_go_to,
		    lang_place_title[places[place].exit_loc[i]]);
}


static void here(int id)
{
    if (id >= 0) {
	printf(lang_thereis_format, lang_thing[id]);
    } else {
	char *p = find_name(id);
	if (p)
	    printf(lang_thereis_format, p);
	else
	    printf("error: unidentified id");
    }
    printf(" (#%d)\n", id);
}


static void arrived(int id)
{
    if (id >= 0) {
	printf("%s %s", lang_thing[id], lang_arrived);
    } else {
	char *p = find_name(id);
	if (p)
	    printf("%s %s", p, lang_arrived);
	else
	    printf("error: unidentified id");
    }
    printf(" (#%d)\n", id);
}


static void departed(int id)
{
    if (id >= 0) {
	printf("%s %s", lang_thing[id], lang_departed);
    } else {
	char *p = find_name(id);
	if (p)
	    printf("%s %s", p, lang_departed);
	else
	    printf("error: unidentified id");
    }
    printf(" (#%d)\n", id);
}


static void pokedby(int id)
{
    if (id >= 0) {
	printf("%s %s", lang_poked_by, lang_thing[id]);
    } else {
	char *p = find_name(id);
	if (p)
	    printf("%s %s", lang_poked_by, p);
	else
	    printf("error: unidentified id");
    }
    printf(" (#%d)\n", id);
}


static void startup_checks()
{
    map_setup();
    if (lang_nplaces != nplaces) {
	fprintf(stderr, "mismatch in 'place' lists\n");
	exit(1);
    }
    if (lang_nthings != n_thing_place) {
	fprintf(stderr, "mismatch in 'thing' lists\n");
	exit(1);
    }
}


static void storename(int id, char *name)
{
    struct namelist *p;
    if ((p = malloc(sizeof(struct namelist))) == NULL
	    || (p->name = malloc(strlen(name) + 1)) == NULL) {
	fprintf(stderr, "out of memory!\n");
	exit(1);
    }
    strcpy(p->name, name);
    p->id = id;
    p->next = names;
    names = p;
}


static void removename(int id)
{
    struct namelist **p;
    for (p = &names; *p && (*p)->id != id; p = &((*p)->next))
	;
    if (*p) {
	struct namelist *old = *p;
	free((*p)->name);
	*p = (*p)->next;
	free(old);
    }
}


static char *find_name(int id)
{
    struct namelist *p;
    for (p = names; p && p->id !=id; p = p->next)
	;
    return(p ? p->name : NULL);
}


static char **explode(char *s)
{
#   define MAXTOKENS 5
    static char *retval[MAXTOKENS + 1];
    int i;
    static char sep[] = " \t\n\r";

    if ((retval[0] = strtok(s, sep)) == NULL)
	return(retval);
    for (i = 1; i < MAXTOKENS && (retval[i] = strtok((char *)NULL, sep)); i++) {
	if (lang_use_tolower) {
	    char *p;
	    for (p = retval[i]; *p; p++)
		if (isascii(*p) && isupper(*p))
		    *p = tolower(*p);
	}
    }
    retval[i] = NULL;
    return(retval);
}


static int parsenumber(char *s)
{
    if (!isalldigits(s)) {
	printf("%s\n", lang_req_obj_number);
	return(-1);
    }
    return(atoi(s));
}
