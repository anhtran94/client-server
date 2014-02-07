#include "mud.h"
#include "lang.h"
#include "nplaces.h"

/* Traditional Chinese language data */
/* Student-contributed -- instructors do not claim accuracy or propriety */

#define NTHINGS 11
int lang_nplaces = NPLACES;
int lang_nthings = NTHINGS;

/* ok to use isupper()/tolower() on user input? */
int lang_use_tolower = 0;

char *lang_directions[6][2] = {
    { "向北", "n" },
    { "向南", "s" },
    { "向西", "w" },
    { "向東", "e" },
    { "向上", "u" },
    { "向下", "d" },
};
char *lang_nosuchexit = "無法往那裡前進。";

char *lang_get = "拿起";
char *lang_drop = "放下";
char *lang_get_nosuch = "在這個地方並無此物號碼。";
char *lang_drop_nosuch = "你的個人物品當中並無此物號碼。";
char *lang_getdrop_explain = "請輸入'%s'跟物號碼。\n";

char *lang_look[2] = { "看", "l" };
char *lang_inv[2] = { "個人物品", "i" };
char *lang_inv_heading = "你現在攜帶著：";
char *lang_inv_nothing = "無物";

char *lang_poke = "戳";
char *lang_poke_explain = "請輸入'%s'跟人物號碼。\n";
char *lang_poked_by = "你被戳了一下，那是";  /* hard to translate into this form */
char *lang_arrived = "來到這裡了。";
char *lang_departed = "離開了。";

char *lang_toolong = "指令過長，請輸入一字或兩字。";
char *lang_huh = "我不懂這個指令。";
char *lang_req_obj_number = "請輸入人物或物品的號碼，而並非它的名稱";
char *lang_commandlist = "請輸入其中一項：";
char *lang_ok = "OK";

/* new text, needs translation: */
char *lang_say = "say";
char *lang_says_format = "%s says:";

char *lang_yesno[2][2] = {
    { "是", "y" },
    { "否", "n" }
};

char *lang_youat = "你在:";
char *lang_youcango = "你可以去";
char *lang_go_to = "到";  /* used like: "north %s the cafeteria" */
char *lang_thereis_format = "這裡%s。";

char *lang_handle_request = "請輸入您的稱呼";

char *lang_place_title[NPLACES] = {
    /*  0 */ "UTM公車站",
    /*  1 */ "Hart House的St. George公車站",
    /*  2 */ "盲鴨啤酒屋",
    /*  3 */ "CCIT建築的大廳",
    /*  4 */ "小型同好會會議室",
    /*  5 */ "UTM Tim Hortons",
    /*  6 */ "體育館",
    /*  7 */ "South建築的西邊電梯", /* %#!@ */
    /*  8 */ "South建築的第三樓",
    /*  9 */ "MCS系辦公室",
    /*  10 */ "Hart House的接待員服務台",
    /*  11 */ "Hart House美麗的音樂廳",
    /*  12 */ "Sandford建築",
    /*  13 */ "Bahen建築的大廳",
    /*  14 */ "CDF研究室",
    /*  15 */ "DCS本科生辦公室"
};

char *lang_place_detail[NPLACES] = {
    /* UTMshuttle */ "學生排了很長的隊伍在等公車。",
    /* STGshuttle */ "優美的音樂由某個窗戶飄出。",
    /* blindduck */ "聽說這裡的啤酒比食物要來的好。",
    /* CCIT */ "最新的藝術展覽有點怪。",
    /* meetingRoom */ 0,
    /* Tims */ "怪了，今天排的隊不長。",
    /* gym */ "所有好的跑步機都有人在用。",
    /* SE  */ "有個廣告說：'花的多，得的少！'", /* vague.. */
    /* SE3rd */ "這邊只有地理學家跟生物學家，你或許應該前往他處。",
    /* MCS */ "秘書和藹可親地協助你。",
    /* HH */ "門房忙著接電話，所以沒有注意到你站在那兒。",
    /* musicRoom */ "好漂亮的房間啊，你真的可以待在這裡嗎？",
    /* SF */ "你躲開一群工程師走音的歌聲。"
    /* BA */ "你原本想在 Megabucks 買杯咖啡，不過最後決定不買。",
    /* cdf */ "工作太多...而時間太少！",
    /* ugo */ 0
};

char *lang_thing[NTHINGS] = {
    /*  0 */ "一個對著手機裡大喊大叫的笨蛋",
    /*  1 */ "一份丟棄的報紙",
    /*  2 */ "一瓶啤酒",
    /*  3 */ "一團揉爛的紙",
    /*  4 */ "一張磁碟片",
    /*  5 */ "一瓶非法易開罐",
    /*  6 */ "一張必要的準免表格",
    /*  7 */ "一份翻翻樂的中獎杯",
    /*  8 */ "一份翻翻樂未中獎的杯子",
    /*  9 */ "一張公車票",
    /* 10 */ "一隻被遺忘的臭襪子",
};
