#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "util.h"


/* match a command name and require an argument */
/* assumes that buf has had a \0 put in at the right place */
int match_arg(char *buf, char *command, int *arg)
{
    int len = strlen(command);
    if (strncmp(buf, command, len) || buf[len] != ' ')
        return(0);
    if (!isdigit(buf[len + 1]) && !(buf[len+1] == '-' && isdigit(buf[len+2])))
        return(0);
    *arg = atoi(buf + len + 1);
    return(1);
}


int isalldigits(char *s)
{
    for (; *s; s++)
	if (!isascii(*s) || !isdigit(*s))
	    return(0);
    return(1);
}


char *memnewline(char *p, int size)  /* finds \r _or_ \n */
	/* This is like min(memchr(p, '\r'), memchr(p, '\n')) */
	/* It is named after memchr().  There's no memcspn(). */
{
    for (; size > 0; p++, size--)
	if (*p == '\r' || *p == '\n')
	    return(p);
    return(NULL);
}
