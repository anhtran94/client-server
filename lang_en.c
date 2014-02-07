#include "mud.h"
#include "lang.h"
#include "nplaces.h"

/* English language data */

#define NTHINGS 11
int lang_nplaces = NPLACES;
int lang_nthings = NTHINGS;

/* ok to use isupper()/tolower() on user input? */
int lang_use_tolower = 1;

char *lang_directions[6][2] = {
    { "north", "n" },
    { "south", "s" },
    { "west", "w" },
    { "east", "e" },
    { "up", "u" },
    { "down", "d" },
};
char *lang_nosuchexit = "There is no way to go that direction.";

char *lang_get = "get";
char *lang_drop = "drop";
char *lang_get_nosuch = "No such object number at this location.";
char *lang_drop_nosuch = "No such object number amongst your possessions.";
char *lang_getdrop_explain = "Say '%s' followed by the number of the object.\n";

char *lang_look[2] = { "look", "l" };
char *lang_inv[2] = { "inv", "i" };
char *lang_inv_heading = "You are currently carrying:";
char *lang_inv_nothing = "Nothing!";

char *lang_poke = "poke";
char *lang_poke_explain = "Say '%s' followed by the number of the person.\n";
char *lang_poked_by = "You have been poked by";
char *lang_arrived = "is now here.";
char *lang_departed = "is no longer here.";

char *lang_toolong = "That command is too long.  Type one or two words.";
char *lang_huh = "I don't understand that command.";
char *lang_req_obj_number = "Sorry, you need to type the object or person's number, not its name.";
char *lang_commandlist = "Type one of:";
char *lang_ok = "OK";

char *lang_say = "say";
char *lang_says_format = "%s says:";

char *lang_yesno[2][2] = {
    { "yes", "y" },
    { "no", "n" }
};

char *lang_youat = "You are at:";
char *lang_youcango = "You can go";
char *lang_go_to = "to";  /* used like: "north %s the cafeteria" */
char *lang_thereis_format = "There is %s here.";

char *lang_handle_request = "Please enter a handle you wish to be known by";

char *lang_place_title[NPLACES] = {
    /*  0 */ "the shuttle bus stop at UTM",
    /*  1 */ "the St. George shuttle bus stop at Hart House",
    /*  2 */ "the Blind Duck pub",
    /*  3 */ "the lobby of the CCIT building",
    /*  4 */ "a small meeting room for student clubs",
    /*  5 */ "the UTM Tim Hortons",
    /*  6 */ "the gymnasium",
    /*  7 */ "the west end elevators of the south building",
    /*  8 */ "the 3rd floor of the south building",
    /*  9 */ "the MCS department office",
    /*  10 */ "the porter's desk in Hart House",
    /*  11 */ "the beautiful Hart House music room",
    /*  12 */ "the Sandford Fleming building",
    /*  13 */ "the lobby of the Bahen building",
    /*  14 */ "the cdf lab",
    /*  15 */ "the DCS undergraduate office"
};

char *lang_place_detail[NPLACES] = {
    /* UTMshuttle */ "There is a huge queue of students waiting for the bus.",
    /* STGshuttle */ "You can hear beautiful music wafting out one of the windows.",
    /* blindduck */ "Supposedly the beer is better than the food.",
    /* CCIT */ "The newest art exhibit is just a little weird.",
    /* meetingRoom */ 0,
    /* Tims */ "Strangely enough the queue isn't very long today.",
    /* gym */ "All the good treadmills seem taken.",
    /* SE  */ "An advertisement says, 'spend more and get less!'",
    /* SE3rd */ "Only geographers and biologists here.  You should probably move on.",
    /* MCS */ "The secretary is very pleasant and offers you assistance.",
    /* HH */ "The porter is too busy on the phone to notice you standing there.",
    /* musicRoom */ "What a gorgeous room.  Are you really allowed to be in here?",
    /* SF */ "You avoid the crowds of engineers singing badly off key.",
    /* BA */ "You wonder about stopping for a coffee at Megabucks but decide against it.",
    /* cdf */ "So much work... so little time.",
    /* ugo */ 0
};

char *lang_thing[NTHINGS] = {
    /*  0 */ "an idiot yelling on a cell phone",
    /*  1 */ "a discarded newspaper",
    /*  2 */ "a beer",
    /*  3 */ "a crumpled piece of paper",
    /*  4 */ "a floppy disk",
    /*  5 */ "an illegal pop can",
    /*  6 */ "a prerequisite waiver form",
    /*  7 */ "a winning roll-up-the-rim cup",
    /*  8 */ "a losing roll-up-the-rim cup",
    /*  9 */ "a bus ticket",
    /* 10 */ "a dirty smelly forgotten sock",
};
