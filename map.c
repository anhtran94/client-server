#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mud.h"
#include "map.h"

/* directions sequence: north, south, west, east, up, down */
struct placeinfo places[] = {
    { "UTMshuttle", { "blindduck", 0, 0, "STGshuttle" } },
    { "STGshuttle", {  0, "SF", "UTMshuttle", 0, "harthouse" } },
    { "blindduck", { 0, "UTMshuttle", 0, "CCIT", "meetingRoom" } },
    { "CCIT", { 0, "UTMshuttle", "blindduck", "SE" } },
    { "meetingRoom", { 0,0,0,0,0, "blindduck" } },
    { "Timmies", { 0, "UTMshuttle", "SE", 0,0, "UTMgym" } },
    { "UTMgym", { 0,0,0,0, "Timmies" } },
    { "SE", { 0, "UTMshuttle", "CCIT", "Timmies", "SE3rdfloor", "UTMgym" } },
    { "SE3rdfloor", { 0,0,0,0, "MCS", "SE" } },
    { "MCS", { 0,0,0,0,0, "SE3rdfloor" } },
    { "harthouse", { 0,0,0,0, "musicRoom", "STGshuttle" } },
    { "musicRoom", { 0,0,0,0,0, "harthouse" } },
    { "SF", { "STGshuttle", 0, "BA", 0,0,0 } },
    { "BA", { "STGshuttle", 0,0, "SF", "cdf" } },
    { "cdf", { 0,0,0,0, "ugo", "BA" } },
    { "ugo", { 0,0,0,0,0, "cdf" } },
};
int nplaces = sizeof places / sizeof places[0];

struct placeindex {
    char *label;
    int index;
};
int mycompare(const void *a, const void *b) {
    return(strcmp(((struct placeindex *)a)->label,((struct placeindex *)b)->label));
}
int myfind(struct placeindex *pi, char *label) {
    struct placeindex key, *result;
    key.label = label;
    result = bsearch(&key, pi, nplaces, sizeof pi[0], mycompare);
    if (!result) {
	fprintf(stderr, "fatal error in map.c: can't find label '%s'\n",
		label);
	exit(1);
    }
    return(result->index);
}


void map_setup()
{
    int i, j;
    struct placeindex pi[sizeof places / sizeof places[0]];

    for (i = 0; i < nplaces; i++) {
	pi[i].label = places[i].label;
	pi[i].index = i;
    }
    qsort(pi, nplaces, sizeof pi[0], mycompare);

    for (i = 0; i < nplaces; i++) {
	for (j = 0; j < NDIRECTIONS; j++) {
	    if (places[i].exit_label[j])
		places[i].exit_loc[j] = myfind(pi, places[i].exit_label[j]);
	    else
		places[i].exit_loc[j] = -1;
	}
    }
}
