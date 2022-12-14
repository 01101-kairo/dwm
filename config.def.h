#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx        = 1;  /* border pixel of windows */
static const unsigned int snap            = 6;  /* snap pixel */
static const unsigned int systraypinning  = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;  /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 2;  /* systray spacing */
static const int systraypinningfailfirst  = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1; /* 0 means no systray */
static const int showbar                  = 1; /* 0 means no bar */
static const int topbar                   = 1;  /* 0 means bottom bar */

static const char *fonts[]                = {"fontawesome:size=13"};
static const char dmenufont[]             = "fontawesome:size=13";
static const char col_gray1[]             = "#000000";
static const char col_gray2[]             = "#f65866";
static const char col_gray3[]             = "#F6F6F6";
static const char col_gray4[]             = "#000000000000";

static const char *colors[][3]            = {
  /*               fg         bg         border   */
  [SchemeNorm] = {col_gray3, col_gray1, col_gray1},
  [SchemeSel]  = {col_gray1, col_gray2, col_gray4},
};

/* tagging */
static const char *tags[] = {"𝟭", "𝟮", "𝟯", "𝟰", "𝟱", "𝟲", "𝟳", "𝟴", "𝟵"};

/**************************************************************** Rules rules*/
static const Rule rules[] = {
  /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
 /* class     instance  title    tags mask  isfloating	monitor */
  {"chromium",  NULL, NULL,                             0, 1, -1},
  {"ranger",    NULL, NULL,                             0, 1, -1},
  {"htop",      NULL, NULL,                             0, 1, -1},
  {NULL,        NULL, "DevTools",                       0, 1, -1},
  {NULL,        NULL, "Telegram",                       0, 1, -1},
  {NULL,        NULL, "WoeUSB-ng",                      0, 1, -1},
  {NULL,        NULL, "GParted",                        0, 1, -1},
  {NULL,        NULL, "xfce4-appfinder",                0, 1, -1},
  {NULL,        NULL, "Localizador de aplicativos",     0, 1, -1},
  {NULL,        NULL, "Qt5 Ferramenta de Configuração", 0, 1, -1},
  {NULL,        NULL, "Personalizar visual",            0, 1, -1},
  {NULL,        NULL, "kdeconnect-ap",                  0, 1, -1},
  {NULL,        NULL, "colorpicker",                    0, 1, -1},
  {NULL,        NULL, "V4L2 Viewer",                    0, 1, -1},
  {NULL,        NULL, "KDE Connect",                    0, 1, -1},
  {NULL,        NULL, "Qt5 Config",                     0, 1, -1},
  {NULL,        NULL, "Kvantum",                        0, 1, -1},
  {NULL,        NULL, "scrcpy",                         0, 1, -1},
  {NULL,        NULL, "feh",                            0, 1, -1},
  {NULL,        NULL, "Firewall",                       0, 1, -1},
  {NULL,        NULL, "Timeshift",                      0, 1, -1},
  {NULL,        NULL, "Screen Layout Editor",           0, 1, -1},
};

/* layout(s) */
static const int    lockfullscreen  = 1;    /* 1 will force focus on the fullscreen window */
static const int    nmaster         = 1;    /* number of clients in master area */
static const int    resizehints     = 0;    /* 1 means respect size hints in tiled resizals */
static const float  mfact           = 0.55; /* factor of master area size [0.05..0.95] */
static const Layout layouts[]       = {
  /* symbol     arrange function */
  {"[]=", tile}, /* first entry is default */
  {"><>", NULL}, /* no layout function means floating behavior */
  {"[M]", monocle},
};

/* key definitions */
#define MODKEY  Mod4Mask
#define ALT     Mod1Mask

#define TAGKEYS(KEY, TAG)                                                     \
  {MODKEY,                            KEY, view,        {.ui = 1 << TAG}},    \
    {MODKEY | ControlMask,              KEY, toggleview,  {.ui = 1 << TAG}},  \
    {MODKEY | ShiftMask,                KEY, tag,         {.ui = 1 << TAG}},  \
    {MODKEY | ControlMask | ShiftMask,  KEY, toggletag,   {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd){.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }}

/*********************************************************************
 * commands*/
static        char dmenumon[2]  =  "0"; /* component of dmenucmd, manipulated in spawn() */
static const  char *dmenucmd[]  =  {"dmenu_run", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", "#353c4b", "-nf", "#fff", "-sb", "#77d5f0", "-sf", "#353c4b", NULL};
static const  char *termcmd[]   =  {"xterm", NULL};

/****************************************************************** atalhos dwm
modifier						    key        function
argument */
static Key keys[] = {
  /* [App's] */
  {0,                   XF86XK_HomePage,          spawn, SHCMD("chromium --force-dark-mode --enable-features=WebUIDarkMode")},
  {0,                   XF86XK_Mail,              spawn, SHCMD("cat $HOME/.config/bin/.tokenGit | xclip -sel clip")},
  {0,                   XF86XK_Explorer,          spawn, SHCMD("~/.config/bin/arand.sh")},
  {0,                   XF86XK_Tools,             spawn, SHCMD("~/.config/bin/pavuqt.sh")},
  {0,                   XF86XK_Calculator,        spawn, SHCMD("xterm -e node")},
  {MODKEY,              XK_e,                     spawn, SHCMD("xterm -e ranger")},
  {MODKEY,              XK_d,                     spawn, SHCMD("xfce4-appfinder")},
  {ControlMask,         XK_Escape,                spawn, SHCMD("~/.config/bin/thop.sh")},
  {MODKEY,              XK_t,                     spawn, SHCMD("~/.config/bin/tt.sh")},
  {MODKEY,              XK_y,                     spawn, SHCMD("~/.config/bin/kp.sh")},
  {ALT,                 XK_b,                     spawn, SHCMD("~/.config/rofi/scripts/rofi-bluetooth;pkill -RTMIN+9 dwmblocks")},
  {MODKEY,              XK_b,                     spawn, SHCMD("~/.config/dwm/scripts/dmenu-bluetooth;pkill -RTMIN+9 dwmblocks")},
  {ALT,                 XK_Delete,                spawn, SHCMD("~/.config/dwm/scripts/powerOff")}, // spawn, SHCMD("xfce4-session-logout")},
  {MODKEY,              XK_n,                     spawn, SHCMD("~/.config/rofi/scripts/rofi-wifi-menu.sh")},
  {MODKEY,              XK_g,                     spawn, SHCMD("~/.config/dwm/scripts/screenRecorder")},
  {0,                   XK_Print,                 spawn, SHCMD("sleep 2; scrot '%Y-%m-%d-%S_%wx%h.png' -e 'mv $f $$HOME/Pictures/screenshots/'")},
  {ALT,                 XK_p,                     spawn, SHCMD("flameshot gui")}, // SHCMD("sleep 1; scrot -s '%Y-%m-%d-%S_$wx$h.png' -e 'mv $f $$HOME/Pictures/screenshots/'")
  {ALT,                 XK_g,                     spawn, SHCMD("exec setxkbmap -query | grep us && setxkbmap -layout br || setxkbmap -layout us;pkill -RTMIN+13 dwmblocks")},

  /* [ Sreen brightness controls ] */
  {ALT,                 XK_Up,                    spawn, SHCMD("brightnessctl set 50+;brightnessctl l|grep -oP \"[^\\(]*%\">$HOME/.config/bin/.luz;pkill -RTMIN+12 dwmblocks")},
  {ALT,                 XK_Down,                  spawn, SHCMD("brightnessctl set 50-;brightnessctl l|grep -oP \"[^\\(]*%\">$HOME/.config/bin/.luz;pkill -RTMIN+12 dwmblocks")},
  {0,                   XF86XK_MonBrightnessUp,   spawn, SHCMD("xbacklight -inc 20")},
  {0,                   XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 20")},

  /* [Play Midia] */   
  {0,                   XF86XK_AudioPrev,         spawn, SHCMD("playerctl previous")},
  {0,                   XF86XK_AudioNext,         spawn, SHCMD("playerctl next")},
  {0,                   XF86XK_AudioPlay,         spawn, SHCMD("playerctl play-pause")},

  
  /* [ Sreen volume controls ] */
  {0,                   XF86XK_AudioRaiseVolume,  spawn, SHCMD("amixer -q -D pulse set Master 5%+;pkill -RTMIN+10 dwmblocks")},
  {0,                   XF86XK_AudioLowerVolume,  spawn, SHCMD("amixer -q -D pulse set Master 5%-;pkill -RTMIN+10 dwmblocks")},
  {0,                   XF86XK_AudioMute,         spawn, SHCMD("amixer -q -D pulse set Master toggle;pkill -RTMIN+10 dwmblocks")},
  
  /* [ Sreen volume microphone controls ] */   
  {ALT,                 XK_equal,                 spawn, SHCMD("amixer set Capture 5%+;pkill -RTMIN+11 dwmblocks")},
  {ALT,                 XK_minus,                 spawn, SHCMD("amixer set Capture 5%-;pkill -RTMIN+11 dwmblocks")},
  {ALT,                 XK_0,                     spawn, SHCMD("amixer set Capture toggle;pkill -RTMIN+11 dwmblocks")},
  {0,                   XF86XK_AudioStop,         spawn, SHCMD("rofi -modi \"clipboard:greenclip print\" -show clipboard -run-command '{cmd}'")},
  
  /*set layouts*/
  {ALT,                 XK_t,                     setlayout,      {.v = &layouts[0]}},
  {ALT,                 XK_f,                     setlayout,      {.v = &layouts[1]}},
  {ALT,                 XK_m,                     setlayout,      {.v = &layouts[2]}},

  /*atalhos*/
  {MODKEY,              XK_space,                 setlayout,      {0}},
  {MODKEY | ShiftMask,  XK_space,                 togglefloating, {0}},
  {MODKEY,              XK_i,                     incnmaster,     {.i = +1}},
  {MODKEY | ShiftMask,  XK_i,                     incnmaster,     {.i = -1}},
  {MODKEY | ShiftMask,  XK_j,                     rotatestack,    {.i = +1}},
  {MODKEY | ShiftMask,  XK_k,                     rotatestack,    {.i = -1}},
  {MODKEY,              XK_j,                     focusstack,     {.i = +1}},
  {MODKEY,              XK_k,                     focusstack,     {.i = -1}},
  {MODKEY,              XK_h,                     setmfact,       {.f = -0.05}},
  {MODKEY,              XK_l,                     setmfact,       {.f = +0.05}},
  {MODKEY,              XK_0,                     view,           {.ui = ~0}},
  {MODKEY | ShiftMask,  XK_0,                     tag,            {.ui = ~0}},
  {MODKEY,              XK_comma,                 focusmon,       {.i = -1}},
  {MODKEY,              XK_period,                focusmon,       {.i = +1}},
  {MODKEY | ShiftMask,  XK_comma,                 tagmon,         {.i = -1}},
  {MODKEY | ShiftMask,  XK_period,                tagmon,         {.i = +1}},
  {MODKEY | ShiftMask,  XK_Return,                zoom,           {0}},
  {MODKEY,              XK_Tab,                   view,           {0}},
  {MODKEY,              XK_q,                     killclient,     {0}},
  {MODKEY | ShiftMask,  XK_g,                     togglebar,      {0}},
  {MODKEY | ShiftMask,  XK_q,                     quit,           {0}},
  /*etiqueta*/
  TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2)
  TAGKEYS(XK_4, 3) TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5)
  TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7) TAGKEYS(XK_9, 8)
};
/*********************************************************** button definitions
click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin,
or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function argument */
  {ClkLtSymbol,   0,     Button1, setlayout,       {0}},
  {ClkLtSymbol,   0,     Button3, setlayout,       {.v = &layouts[2]}},
  {ClkWinTitle,   0,     Button2, zoom,            {0}},
  {ClkStatusText, 0,     Button2, spawn,           {.v = termcmd}},
  {ClkClientWin, MODKEY, Button1, movemouse,       {0}},
  {ClkClientWin, MODKEY, Button2, togglefloating,  {0}},
  {ClkClientWin, MODKEY, Button3, resizemouse,     {0}},
  {ClkTagBar,     0,     Button1, view,            {0}},
  {ClkTagBar,     0,     Button3, toggleview,      {0}},
  {ClkTagBar,    MODKEY, Button1, tag,             {0}},
  {ClkTagBar,    MODKEY, Button3, toggletag,       {0}},
};
