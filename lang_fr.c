#include "mud.h"
#include "lang.h"
#include "nplaces.h"

/* French language data */

#define NTHINGS 11
int lang_nplaces = NPLACES;
int lang_nthings = NTHINGS;

/* ok to use isupper()/tolower() on user input? */
int lang_use_tolower = 1;

char *lang_directions[6][2] = {
    { "nord", "n" },
    { "sud", "s" },
    { "ouest", "o" },
    { "est", "e" },
    { "haut", "h" },
    { "bas", "b" },
};
char *lang_nosuchexit = "Ce n'est pas possible d'aller dans cette direction.";

char *lang_get = "prendre";
char *lang_drop = "laisser";
char *lang_get_nosuch = "L'objet avec cette nombre n'est pas ici.";
char *lang_drop_nosuch = "Vous n'avez pas l'objet avec cette nombre.";
char *lang_getdrop_explain = "Dire '%s' suivi par le nombre de l'objet.\n";

char *lang_look[2] = { "regarder", "r" };
char *lang_inv[2] = { "inv", "i" };
char *lang_inv_heading = "Vous avez maintenant:";
char *lang_inv_nothing = "Rien!";

char *lang_poke = "poke";
char *lang_poke_explain = "Dire '%s' suivi par le nombre de la personne.\n";
char *lang_poked_by = "Vous avez été envoyé un poke par";
char *lang_arrived = "est arrivé(e).";
char *lang_departed = "n'est plus ici.";

char *lang_toolong = "Cette commande est trop longue.  Ecrire un ou deux mots.";
char *lang_huh = "Je ne comprends pas cette commande.";
char *lang_req_obj_number = "Désolé, vous devez écrire la nombre de l'objet ou de la personne, pas son nom.";
char *lang_commandlist = "Ecrire un de ce qui suit:";
char *lang_ok = "OK";

char *lang_say = "dire";
char *lang_says_format = "%s dit:";

char *lang_yesno[2][2] = {
    { "oui", "o" },
    { "non", "n" }
};

char *lang_youat = "Vous êtes à:";
char *lang_youcango = "Vous pouvez aller";
char *lang_go_to = "à";  /* used like: "north %s the cafeteria" */
char *lang_thereis_format = "Il y a %s ici.";

char *lang_handle_request = "Veuillez écrire un «handle» que vous souhaitez être connu par";

char *lang_place_title[NPLACES] = {
    /*  0 */ "l'arrêt de navette à UTM",
    /*  1 */ "l'arrêt de navette à St George",
    /*  2 */ "le pub «Blind Duck»",
    /*  3 */ "l'entrée de l'édifice CCIT",
    /*  4 */ "un petit lieu de réunion pour des clubs d'étudiant(e)",
    /*  5 */ "le Tim Hortons à UTM",
    /*  6 */ "le gymnase",
    /*  7 */ "les ascenseurs de l'ouest de l'édifice South Building",
    /*  8 */ "la troisième étage de l'édifice South Building",
    /*  9 */ "le bureau de département d'MCS",
    /* 10 */ "le bureau de portier de Hart House",
    /* 11 */ "la belle salle de musique de Hart House",
    /* 12 */ "l'édifice Sandford Fleming",
    /* 13 */ "l'entrée de l'édifice Bahen",
    /* 14 */ "le labo CDF",
    /* 15 */ "le bureau d'étudiant(e)s de DCS",
};

char *lang_place_detail[NPLACES] = {
    /* UTMshuttle */ "Il y a une énorme file d'étudiants attendant l'autobus.",
    /* STGshuttle */ "Vous pouvez entendre de la belle musique dehors une des fenêtres.",
    /* blindduck */ "Censément la bière est meilleure que le mangee.",
    /* CCIT */ "L'objet exposé d'art le plus nouveau est un peu étrange.",
    /* meetingRoom */ 0,
    /* Timmies */ "Étrangement, la file n'est pas très long aujourd'hui.",
    /* UTMgym */ "Tous les bons tapis semblent être pris.",
    /* SE */ "Une publicité indique: «Dépensez plus! Obtenez moins!»",
    /* SE3rd */ "Seulement géographes et biologistes ici.  Probablement vous deriez passer.",
    /* MCS */ "Le secrétaire est très plaisant et vous offre l'aide.",
    /* harthouse */ "Le portier est trop occupé au téléphone pour vous apercevoir.",
    /* musicRoom */ "Quelle salle magnifique.  Est-ce qu'on vous permet vraiment d'être ici?",
    /* SF */ "Vous évitez les foules des ingénieurs chantant mal.",
    /* BA */ "Vous vous demander d'arrêter pour un café Megabucks, mais décidez de ne pas le faire.",
    /* cdf */ "Tant de travail... si peu d'heures.",
    /* ugo */ 0,
};

char *lang_thing[NTHINGS] = {
    /*  0 */ "un idiot qui hurle à un téléphone portable",
    /*  1 */ "un journal jeté",
    /*  2 */ "une bière",
    /*  3 */ "un papier chiffonné",
    /*  4 */ "une disquette",
    /*  5 */ "un peut de soude illégal",
    /*  6 */ "une forme intitulé «prerequisite waiver»",
    /*  7 */ "une tasse «déroule le rebord» gagnante",
    /*  8 */ "une tasse «déroule le rebord» perdante",
    /*  9 */ "un billet de navette",
    /* 10 */ "une chausette salée, malodorante, et oubliée",
};
