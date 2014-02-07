#include "mud.h"
#include "lang.h"
#include "nplaces.h"

/* Indonesian language data by Johan Harjono and Nathaniel Margono */
/* Student-contributed -- instructors do not claim accuracy or propriety */

#define NTHINGS 11
int lang_nplaces = NPLACES;
int lang_nthings = NTHINGS;

/* ok to use isupper()/tolower() on user input? */
int lang_use_tolower = 1;

char *lang_directions[6][2] = {
    { "utara", "n" },
    { "selatan", "s" },
    { "barat", "w" },
    { "timur", "e" },
    { "atas", "u" },
    { "bawah", "d" },
};
char *lang_nosuchexit = "Maaf anda tidak bisa kesana";

char *lang_get = "ambil";
char *lang_drop = "taruh";
char *lang_get_nosuch = "Tidak ada barang di lokasi ini";
char *lang_drop_nosuch = "Tidak punya barang ini.";
char *lang_getdrop_explain = "Bilang '%s' diikuti dengan nomor barang ini.\n";

char *lang_look[2] = { "lihat", "l" };
char *lang_inv[2] = { "inv", "i" };
char *lang_inv_heading = "Anda saat ini sedang membawah:";
char *lang_inv_nothing = "Tidak ada";

char *lang_poke = "Tusuk";
char *lang_poke_explain = "Bilang '%s' diikuti dengan nomor orang ini.\n";
char *lang_poked_by = "Anda ditusuk sama";
char *lang_arrived = "sekarang ada di sini";
char *lang_departed = "sudah tidak ada di sini";

char *lang_toolong = "Instruksi terlalu panjang.  Ketik satu atau dua kata-kata.";
char *lang_huh = "Saya tidak mengerti instruksi ini.";
char *lang_req_obj_number = "Maaf, Anda perlu mengetik tipenya barang atau nomornya orang, bukan namanya.";
char *lang_commandlist = "Tolong ketik salah satu:";
char *lang_ok = "OK";

/* new text, needs translation: */
char *lang_say = "say";
char *lang_says_format = "%s says:";

char *lang_yesno[2][2] = {
    { "ya", "y" },
    { "tidak", "n" }
};

char *lang_youat = "Anda ada di:";
char *lang_youcango = "Anda bisa ke";
char *lang_go_to = "ke";  /* used like: "north %s the cafeteria" */
char *lang_thereis_format = "Ada %s di sini.";

char *lang_handle_request = "Tolong masukkan handel yang anda mau diidentifikasikan dengan";

char *lang_place_title[NPLACES] = {
    /*  0 */ "Terminal Bis UTM",
    /*  1 */ "Terminal Bis St. George di Hart House",
    /*  2 */ "bar \"Blind Duck\"",
    /*  3 */ "lobi bangunan CCIT",
    /*  4 */ "ruangan kecil untuk pertemuan organisasi pelajar",
    /*  5 */ "Tim Hortons UTM",
    /*  6 */ "lapangan perolahraga",
    /*  7 */ "elevator barat di bangunan selatan",
    /*  8 */ "lantai ketiga di bangunan selatan",
    /*  9 */ "Kantor departement MCS",
    /*  10 */ "meja porter Hart House",
    /*  11 */ "ruangan musik yang indah di Hart House",
    /*  12 */ "bangunan Sandford Fleming",
    /*  13 */ "lobi bangunan Bahen",
    /*  14 */ "lab cdf",
    /*  15 */ "kantor mahasiswa DCS"
};

char *lang_place_detail[NPLACES] = {
    /* UTMshuttle */ "Ada barisan pelajar yang penuh menungguhi bis.",
    /* STGshuttle */ "Anda bisa mendengar musik yang indah keluar dari salah satu jendela.",
    /* blindduck */ "Katanya bir itu lebih enak dari pada makanannya.",
    /* CCIT */ "Pameran seni yang paling baru itu sedikit aneh.",
    /* meetingRoom */ 0,
    /* Tims */ "Anehnya, barisannya hari ini tidak terlalu panjang.",
    /* gym */ "Semua treadmill yang bagus sepertinya sudah dipakai.",
    /* SE  */ "Satu iklan bilang, 'beli lebih banyak dapat lebih sedikit!'",
    /* SE3rd */ "Cuma orang geographi dan orang biologi di sini. Mungkin lebih baik anda terus saja.",
    /* MCS */ "Sekretarinya baik dan menawarkan pembantuan.",
    /* HH */ "Porternya terlalu sibuk menelpon untuk melihat anda berdiri di sana.",
    /* musicRoom */ "Wah ruangan yang indah. Apakah anda benar-benar boleh ada di sini?",
    /* SF */ "Anda menghindar kerumunan insinyur yang sedang menyanyi fales.",
    /* BA */ "Anda sedang memikir tentang membeli kopi di Megabucks, tapi tidak jadi.",
    /* cdf */ "Banyak kerjaan...  kurang waktu.",
    /* ugo */ 0
};

char *lang_thing[NTHINGS] = {
    /*  0 */ "Ada orang idiot teriak-teriak di hand phone",
    /*  1 */ "koran yang terbuang",
    /*  2 */ "bir",
    /*  3 */ "kertas yang terremas",
    /*  4 */ "disket",
    /*  5 */ "illegal kaleng",
    /*  6 */ "formulir persyaratan",
    /*  7 */ "roll-up-the-rim gelas kertas yang menang",
    /*  8 */ "roll-up-the-rim gelas kertas yang kalah",
    /*  9 */ "tiket bis",
    /* 10 */ "kaus kaki yang bau dan tertinggal",
};
