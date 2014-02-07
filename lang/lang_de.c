#include "mud.h"
#include "lang.h"
#include "nplaces.h"

/* German language data */
/* Student-contributed -- instructors do not claim accuracy or propriety */

#define NTHINGS 11
int lang_nplaces = NPLACES;
int lang_nthings = NTHINGS;

/* ok to use isupper()/tolower() on user input? */
int lang_use_tolower = 1;

char *lang_directions[6][2] = {
    { "norden", "n" },
    { "süden", "s" },
    { "westen", "w" },
    { "osten", "o" },
    { "oben", "oben" },
    { "unten", "u" },
};
char *lang_nosuchexit = "Es ist nicht möglich in diese Richtung zu gehen.";

char *lang_get = "aufheben";
char *lang_drop = "ablegen";
char *lang_get_nosuch = "Diese Objektnummer gibt es nicht an dieser Stelle.";
char *lang_drop_nosuch = "Diese Objektnummer ist nicht in Ihrem Besitz.";
char *lang_getdrop_explain = "Geben Sie '%s' gefolgt von der Nummer des Objekts ein.\n";

char *lang_look[2] = { "sehen", "l" };
char *lang_inv[2] = { "inventar", "i" };
char *lang_inv_heading = "Sie befördern im Moment:";
char *lang_inv_nothing = "Nichts!";

char *lang_poke = "stoßen";
char *lang_poke_explain = "Geben Sie '%s' gefolgt von der Nummer der Person ein.\n";
char *lang_poked_by = "Sie wurden gestoßen von";
char *lang_arrived = "ist jetzt hier.";
char *lang_departed = "ist nicht mehr hier.";

char *lang_toolong = "Das Kommando ist zu lang.  Geben Sie ein oder zwei Worte ein.";
char *lang_huh = "Ich verstehe das Kommando nicht.";
char *lang_req_obj_number = "Bedauere, Sie müssen die Objekt- oder die Personennummer eingeben, nicht den Namen.";
char *lang_commandlist = "Geben Sie eines der folgenden ein:";
char *lang_ok = "OK";

char *lang_say = "sagen";
char *lang_says_format = "%s sagt:";

char *lang_yesno[2][2] = {
    { "ja", "j" },
    { "nein", "n" }
};

char *lang_youat = "Hier ist:";
char *lang_youcango = "Sie können gehen";
char *lang_go_to = "nach";  /* used like: "north %s the cafeteria" */
char *lang_thereis_format = "Hier liegt %s.";

char *lang_handle_request = "Bitte geben Sie einen Namen für sich selbst ein";

char *lang_place_title[NPLACES] = {
    /*  0 */ "die UTM Shuttlebushaltestelle",
    /*  1 */ "die St. George Shuttlebushaltestelle (Hart House)",
    /*  2 */ "die Kneipe \"Blind Duck\"",
    /*  3 */ "die Empfangshalle des CCIT Gebäude",
    /*  4 */ "ein kleiner Sitzungsraum für Studentenclubs",
    /*  5 */ "das UTM Tim Hortons",
    /*  6 */ "die Turnhalle",
    /*  7 */ "die westlichen Aufzüge des südlichen Gebäudes",
    /*  8 */ "der dritte Stock des südlichen Gebäudes.",
    /*  9 */ "das MCS Institutsbüro",
    /*  10 */ "der Portierschalter vom Hart House",
    /*  11 */ "der schöne Hart House Musikraum",
    /*  12 */ "das Sandford Fleming Gebäude",
    /*  13 */ "die Empfangshalle des Bahen Gebäudes",
    /*  14 */ "das CDF Labor",
    /*  15 */ "das DCS Büro"
};

char *lang_place_detail[NPLACES] = {
    /* UTMshuttle */ "Es wartet eine lange Schlange von Studenten auf den Bus.",
    /* STGshuttle */ "Sie hören schöne Musik aus einem der Fenster dringen.",
    /* blindduck */ "Angeblich ist das Bier besser als das Essen.",
    /* CCIT */ "Die neueste Kunstausstellungg ist nur ein wenig seltsam.",
    /* meetingRoom */ 0,
    /* Tims */ "Seltsamerweise ist die Schlange heute nicht sehr lang.",
    /* gym */ "Alle guten Laufbänder sind besetzt.",
    /* SE  */ "Die Werbung liest, 'Sie geben mehr und bekommen weniger!'",
    /* SE3rd */ "Es sind nur Geographen und Biologen hier.  Wahrscheinlich sollten Sie weitergehen.",
    /* MCS */ "Der Sekretär ist sehr nett und bietet Ihnen Hilfe an.",
    /* HH */ "Der Portier ist zu beschäftigt mit Telefonieren um Sie zu bemerken.",
    /* musicRoom */ "Was für ein wunderschöner Raum.  Dürfen Sie denn hier sein?",
    /* SF */ "Sie vermeiden die Massen von Ingenieuren, die völlig falsch singen.",
    /* BA */ "Sie denken über einen Kaffeestop bei Megabucks nach, entscheiden sich aber dagegen.",
    /* cdf */ "So viel Arbeit... so wenig Zeit.",
    /* ugo */ 0
};

char *lang_thing[NTHINGS] = {
    /*  0 */ "ein Idiot schreit am Handy.",
    /*  1 */ "eine weggeworfene Zeitung",
    /*  2 */ "ein Bier",
    /*  3 */ "ein zerknülltes Blatt Papier",
    /*  4 */ "eine Diskette",
    /*  5 */ "eine illegale Limodose",
    /*  6 */ "ein Formular zur Befreiung der Kursvoraussetzung",
    /*  7 */ "eine 'roll-up-the-rim' Gewinntasse",
    /*  8 */ "eine 'roll-up-the-rim' Verlierertasse",
    /*  9 */ "ein Busticket",
    /* 10 */ "eine schmutzige, stinkende, vergesse Socke",
};
