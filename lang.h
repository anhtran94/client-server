/* #include "mud.h" before #including me */


extern int lang_nplaces;
extern int lang_nthings;

/* ok to use isupper()/tolower() on user input? */
extern int lang_use_tolower;

extern char *lang_directions[NDIRECTIONS][2];
extern char *lang_nosuchexit;

extern char *lang_get;
extern char *lang_drop;
extern char *lang_get_nosuch;
extern char *lang_drop_nosuch;
extern char *lang_getdrop_explain;

extern char *lang_look[2];
extern char *lang_inv[2];
extern char *lang_inv_heading;
extern char *lang_inv_nothing;

extern char *lang_poke;
extern char *lang_poke_explain;
extern char *lang_poked_by;
extern char *lang_arrived;
extern char *lang_departed;

extern char *lang_toolong;
extern char *lang_huh;
extern char *lang_req_obj_number;
extern char *lang_commandlist;
extern char *lang_ok;

extern char *lang_say;
extern char *lang_says_format;

extern char *lang_yesno[2][2];

extern char *lang_youat;
extern char *lang_youcango;
extern char *lang_youcango_or;
extern char *lang_youcango_only;
extern char *lang_go_to;  /* used like:  "north %s the cafeteria" */
extern char *lang_thereis_format;

extern char *lang_handle_request;  /* for the network version only */

extern char *lang_place_title[], *lang_place_detail[];

extern char *lang_thing[];
