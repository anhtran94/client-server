#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mud.h"
#include "lang.h"
#include "map.h"
#include "things.h"
#include "util.h"

static void docmd(char **cmd);
static void get(int obj);
static void drop(int obj);
static void call_with_arg(void (*f)(int), char *arg, char *expln, char *cmdname);
static void inventory();
static void go(int dir);
static void help();
static void describe(int place);
static void startup_checks();
static char **explode(char *s);
static int parsenumber(char *s);

static int mylocation = INITIAL_LOC;


int main()
{
    char buf[80];
    startup_checks();
    describe(mylocation);
    while (putchar('>'), fgets(buf, sizeof buf, stdin))
	docmd(explode(buf));
    return(0);
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
	describe(mylocation);
	return;
    }
    if (strcmp(cmd[0], lang_inv[0]) == 0
	    || strcmp(cmd[0], lang_inv[1]) == 0) {
	inventory();
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
	describe(mylocation);
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
    if (obj >= 0 && obj < n_thing_place && thing_place[obj] == mylocation) {
	thing_place[obj] = -1;
	printf("%s\n", lang_ok);
    } else {
	printf("%s\n", lang_get_nosuch);
    }
}


static void drop(int obj)
{
    if (obj >= 0 && obj < n_thing_place && thing_place[obj] == -1) {
	thing_place[obj] = mylocation;
	printf("%s\n", lang_ok);
    } else {
	printf("%s\n", lang_drop_nosuch);
    }
}


static void inventory()
{
    int i, something = 0;
    printf("%s\n", lang_inv_heading);
    for (i = 0; i < n_thing_place; i++) {
	if (thing_place[i] == -1) {
	    something = 1;
	    printf("    %s (#%d)\n", lang_thing[i], i);
	}
    }
    if (!something)
	printf("%s\n", lang_inv_nothing);
}


static void go(int dir)
{
    if (places[mylocation].exit_loc[dir] >= 0)
	mylocation = places[mylocation].exit_loc[dir];
    else
	printf("%s\n", lang_nosuchexit);
    describe(mylocation);
}


static void help()
{
    int i;
    printf("%s %s %s %s", lang_commandlist, lang_get, lang_drop, lang_inv[0]);
    for (i = 0; i < 6; i++)
	printf(" %s", lang_directions[i][0]);
    printf("\n");
}


static void describe(int place)
{
    int i;
    printf("\n%s %s.\n", lang_youat, lang_place_title[place]);
    if (lang_place_detail[place])
	printf("%s\n", lang_place_detail[place]);

    for (i = 0; i < lang_nthings; i++) {
	if (thing_place[i] == place) {
	    printf(lang_thereis_format, lang_thing[i]);
	    printf(" (#%d)\n", i);
	}
    }

    printf("%s:\n", lang_youcango);
    for (i = 0; i < NDIRECTIONS; i++)
	if (places[place].exit_loc[i] >= 0)
	    printf("    %s %s: %s\n", lang_directions[i][0], lang_go_to,
		    lang_place_title[places[place].exit_loc[i]]);
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
