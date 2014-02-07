#include "mud.h"
#include "lang.h"
#include "nplaces.h"

/* Farsi language data by Hossein Kolahdoozan */
/* Student-contributed -- instructors do not claim accuracy or propriety */

#define NTHINGS 11
int lang_nplaces = NPLACES;
int lang_nthings = NTHINGS;

/* ok to use isupper()/tolower() on user input? */
int lang_use_tolower = 1;

char *lang_directions[6][2] = {
    { "shomal", "s" },
    { "jonoob", "j" },
    { "gharb", "g" },
    { "sHargh", "h" },
    { "bala", "b" },
    { "payeen", "p" },
};
char *lang_nosuchexit = "Be an samt nemishavad harekat kard.";

char *lang_get = "daryaft";
char *lang_drop = "andakhtan";
char *lang_get_nosuch = "Cheneen shomareye sheyEe dar een makan vojood nadarad.";
char *lang_drop_nosuch = "Cheneen shomareye sheyEe dar miyane darayihaye shoma vojood nadarad.";
char *lang_getdrop_explain = "Begoo '%s' donbal shodeh ba shomareye shey.\n";

char *lang_look[2] = { "bebin", "l" };
char *lang_inv[2] = { "inv", "i" };
char *lang_inv_heading = "Shoma dar hale hazer haml mikonid:";
char *lang_inv_nothing = "Hichi!";

char *lang_poke = "sikhoonak";
char *lang_poke_explain = "Begoo '%s' donbal shodeh ba shomareye shakhs.\n";
char *lang_poked_by = "Shoma tavasote een shakhs sikhoonak shodid";
char *lang_arrived = "hala injast.";
char *lang_departed = "digar inja nist.";

char *lang_toolong = "An farman ziyadi boland ast. Yek ya do kalameh type kon.";
char *lang_huh = "Man farmaneh shoma ra dark nemikonam.";
char *lang_req_obj_number = "Bebakhshid shoma bayad shomareye shey ya shakhs ra type konid, na esmeshan.";
char *lang_commandlist = "Yeki as eenhara type kon:";
char *lang_ok = "BASHE";

/* new text, needs translation: */
char *lang_say = "say";
char *lang_says_format = "%s says:";

char *lang_yesno[2][2] = {
    { "are", "a" },
    { "na", "n" }
};

char *lang_youat = "Shoma eenja hastid:";
char *lang_youcango = "Mitavani beravi";
char *lang_go_to = "be tarafe";  /* used like: "north %s the cafeteria" */
char *lang_thereis_format = "Eenja %s hast.";

char *lang_handle_request = "Lotfan esmi ra ke mikhahid tavasote an shenasayi beshavid vared konid";

char *lang_place_title[NPLACES] = {
    /*  0 */ "eestgahe otoboose shuttle UTM",
    /*  1 */ "eestgahe otoboose shuttle St. George dar Hart House",
    /*  2 */ "meykhaneye Blind Duck",
    /*  3 */ "Saloneh sakhtemane CCIT",
    /*  4 */ "otaghe jalaseye koochak baraye goroohaye daneshjooyi",
    /*  5 */ "Tim Hortoneh UTM",
    /*  6 */ "varzeshgah",
    /*  7 */ "asansorhaye samte gharbeh sakhtemane jonoobi",
    /*  8 */ "tabagheye 3 sakhtemaneh jonoobi",
    /*  9 */ "daftare departemaneh MCS",
    /*  10 */ "mizeh sharik dar Hart House",
    /*  11 */ "otaghe moosighiye zibaye Hart House",
    /*  12 */ "sakhtemaneh Sandford Fleming",
    /*  13 */ "Saloneh voroodiye sakhtemaneh Bahen",
    /*  14 */ "mahalle computerhaye cdf",
    /*  15 */ "daftareh undergraduate DCS"
};

char *lang_place_detail[NPLACES] = {
    /* UTMshuttle */ "Safe besyar bozorgi az daneshjoo montazereh otoboos hastand.",
    /* STGshuttle */ "Mitavanid sedaye zibaye moosighi ra ke az birooni yeki az panjereha miayad beshnavid.",
    /* blindduck */ "Mesle eenke abe joyash behtar az ghazayash ast.",
    /* CCIT */ "Jadidtarin namayeshgahe honar ta hodoodi ajeeb ast.",
    /* meetingRoom */ 0,
    /* Tims */ "Safe emrooz be tarzeh ajibi kootah ast.",
    /* gym */ "Mesle eenkeh treadmillhaye khoob gerefteh shodand.",
    /* SE  */ "Tablighi migooyad, 'Bishtar kharj konid va kamtar begirid!'",
    /* SE3rd */ "Eenja faghat goghraphidanan va zistshenasan hastand, behtar ast keh harekat konid.",
    /* MCS */ "Monshi kheyli delnesheen ast va be shoma pishnahadeh komak midahad.",
    /* HH */ "Darban paye telefon mashghool ast va motevajehe shoma nemishavad.",
    /* musicRoom */ "Ajab otaghe zibayi. Aya vaghean ejazeh dari dar eenja bashi?",
    /* SF */ "Az goroohe mohandesini ke ba sedaye bad avaz mikhanad doori mikoni.",
    /* BA */ "Darbareye gereftaneh yek ghahveh az Megabuck fekr mikoni vali tasmimat avaz mishavad.",
    /* cdf */ "Kar kheyli ziyad ast... amma vaght kheyli kam.",
    /* ugo */ 0
};

char *lang_thing[NTHINGS] = {
    /*  0 */ "Ahmaghi dar haleh dad zadan paye telefone hamrahash",
    /*  1 */ "rooznameyi vel shodeh",
    /*  2 */ "yek shisheh abe jo",
    /*  3 */ "tekke kaghaze mochaleh shodeh",
    /*  4 */ "yek diskette",
    /*  5 */ "ghootiye yek nooshabeye gheyre ghanooni",
    /*  6 */ "formeh batel kardaneh yek pishniaz",
    /*  7 */ "yek livaneh barandeye mosabegheye roll-up-the-rim",
    /*  8 */ "yek livaneh bazandeyeh mosabegheye roll-up-the-rim",
    /*  9 */ "yek beleeteh otoboos",
    /* 10 */ "yek joorabeh kasifeh boogandoo",
};
