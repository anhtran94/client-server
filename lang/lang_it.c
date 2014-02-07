#include "mud.h"
#include "lang.h"
#include "nplaces.h"

/* Italian language data */
/* Student-contributed -- instructors do not claim accuracy or propriety */

#define NTHINGS 11
int lang_nplaces = NPLACES;
int lang_nthings = NTHINGS;

/* ok to use isupper()/tolower() on user input? */
int lang_use_tolower = 1;

char *lang_directions[6][2] = {
    { "nord", "n" },
    { "sud", "s" },
    { "ovest", "o" },
    { "est", "e" },
    { "su", "u" },
    { "giù", "d" },
};
char *lang_nosuchexit = "Non c'è modo di passare questa direzione.";

char *lang_get = "ottenere";
char *lang_drop = "goccia";
char *lang_get_nosuch = "Non tale numero oggetto in questa località.";
char *lang_drop_nosuch = "Nessun oggetto numero tra i vostri beni.";
char *lang_getdrop_explain = "Di '%s' seguito dal numero di oggetto.\n";

char *lang_look[2] = { "vedere", "l" };
char *lang_inv[2] = { "inv", "i" };
char *lang_inv_heading = "Si stanno attuando:";
char *lang_inv_nothing = "Niente!";

char *lang_poke = "spingere";
char *lang_poke_explain = "Di '%s' seguito dal numero della persona.\n";
char *lang_poked_by = "Lei è stato spinto da";
char *lang_arrived = "ora è qui.";
char *lang_departed = "non è più qui.";

char *lang_toolong = "Questo comando è troppo lungo. Dire una o due parole.";
char *lang_huh = "Io non capisco questo comando.";
char *lang_req_obj_number = "Siamo spiacenti, è necessario digitare l'oggetto o il numero della persona, non il suo nome.";
char *lang_commandlist = "Digitare uno dei seguenti:";
char *lang_ok = "OK";

char *lang_say = "dire";
char *lang_says_format = "%s dice:";

char *lang_yesno[2][2] = {
    { "si", "y" },
    { "non", "n" }
};

char *lang_youat = "Sei in:";
char *lang_youcango = "Puoi andare";
char *lang_go_to = "alla";  /* used like: "north %s the cafeteria" */
char *lang_thereis_format = "Sta una %s qui.";

char *lang_handle_request = "Si prega di inserire un nome che deve essere conosciuto da";

char *lang_place_title[NPLACES] = {
    /*  0 */ "alla fermata del UTM autobus stazione",
    /*  1 */ "alla fermata del St. George autobus stazione",
    /*  2 */ "il Blind Duck pub",
    /*  3 */ "la lobby del CCIT edificio",
    /*  4 */ "una piccola sala riunioni per i club di studenti",
    /*  5 */ "il UTM Tim Hortons",
    /*  6 */ "la palestra",
    /*  7 */ "ovest ascensori del edificio sud",
    /*  8 */ "al 3° piano del palazzo a sud",
    /*  9 */ "il MCS reparto ufficio",
    /*  10 */ "il portiere della scrivania in Hart House",
    /*  11 */ "la bella sala musica in Hart House",
    /*  12 */ "il Sandford Fleming edificio",
    /*  13 */ "la lobby del Bahen edificio",
    /*  14 */ "il cdf lab",
    /*  15 */ "il DCS sotto laureato ufficio"
};

char *lang_place_detail[NPLACES] = {
    /* UTMshuttle */ "C'è una enorme coda di studenti in attesa del bus.",
    /* STGshuttle */ "È possibile ascoltare la musica bella in unda delle finestre.",
    /* blindduck */ "Presumibilmente la birra è meglio che il cibo.",
    /* CCIT */ "The newest art exhibit is just a little weird.",
    /* meetingRoom */ 0,
    /* Tims */ "Curiosamente la coda non è molto lungo oggi.",
    /* gym */ "Tutte le buone Treadmills sembrano presa.",
    /* SE  */ "Un annuncio dice, 'spendere di più e avere meno",
    /* SE3rd */ "Solo i geografi e biologi qui. Si dovrebbe probabilmente passare.",
    /* MCS */ "Il segretario è molto piacevole e offre assistenza.",
    /* HH */ "Il portiere è troppo occupato sul telefono per vi avedere.",
    /* musicRoom */ "What a gorgeous room.  Are you really allowed to be in here?",
    /* SF */ "È evitare la folla di ingegneri chi cantono male.",
    /* BA */ "Se chiedo di arresto per un espresso o capuccino a, ma decidere di contro di essa.",
    /* cdf */ "Tanto lavoro... così poco tempo.",
    /* ugo */ 0
};

char *lang_thing[NTHINGS] = {
    /*  0 */ "un testa di cazzo urlare su un telefono cellulare",
    /*  1 */ "uno scartato giornale",
    /*  2 */ "una bira",
    /*  3 */ "uno spiegazzato pezzo di carta",
    /*  4 */ "un floppy disk",
    /*  5 */ "uno illegale bottiglia di pop",
    /*  6 */ "una condizione indispensabile forma di rinuncia",
    /*  7 */ "una vincente roll-up-the-rim tazza",
    /*  8 */ "una predente roll-up-il-cerchio tazza",
    /*  9 */ "un biglietto",
    /* 10 */ "una sporca dimenticata calza puzzolente",
};
