/* #include "mud.h" before #including me */


struct placeinfo {
    /* names displayed to user are in lang_??.c files */
    char *label;  /* internal name, easier than numbers, like an asm label */
    char *exit_label[NDIRECTIONS];  /* labels for exits */
    int exit_loc[NDIRECTIONS];  /* integer values of those places */
};

extern struct placeinfo places[];
extern int nplaces;

extern void map_setup();
