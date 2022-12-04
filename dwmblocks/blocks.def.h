#define SC(ruta) "/home/kairo/.config/bin/blocks/" #ruta
// Modify this file to change what commands output to your statusbar, and
// recompile using the make command.
static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/
    /* {" ", "date '+%d %b (%a)'",                                             5, 0 },
    {" ", "date '+%H:%M%p'",                                                5, 0 }, */
    {"",    SC("bluetooth"),                                                 0, 9 },
    {"",    SC("audio"),                                                     0, 10},
    {"",    SC("microphone"),                                                0, 11},
    {" ",  SC("network"),                                                   1, 0 },
    {" ",  "free -h|awk '/^Mem/ { print $3\"/\"$2 }'|sed s/i//g",           1, 0 },
    {" ",  "free -h|awk '/^Swap/ { print $3\"/\"$2 }'|sed s/i//g",          1, 0 },
    {" ",  SC("cpu"),                                                       1, 0 },
    {" ",  SC("temperature"),                                               1, 0 },
    {" ",  "setxkbmap -query|grep -oP us || setxkbmap -query |grep -oP br", 2, 13},
};
// sets delimeter between status commands. NULL character ('\0') means no
// delimeter.
static char delim[] = "   ";
static unsigned int delimLen = 5;
