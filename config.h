/* Author: Rafael Cavalcanti <https://rafaelc.org/dev>
 * Based on dwm original configuration. */

/* See LICENSE file for copyright and license details. */

/* For multimedia keys */
#include <X11/XF86keysym.h>

/* For extra mouse buttons */
#define Button6 6
#define Button7 7
#define Button8 8
#define Button9 9

/* appearance */
static unsigned int borderpx = 1;  /* border pixel of windows */
static unsigned int snap = 32;  /* snap pixel */
static int showbar = 1;   /* 0 means no bar */
static int topbar = 1;   /* 0 means bottom bar */
static char font[] = "monospace:size=10";
static char dmenufont[] = "monospace:size=10";
static const char *fonts[] = { font };
static const unsigned int gappih = 16;  /* horiz inner gap between windows */
static const unsigned int gappiv = 16;  /* vert inner gap between windows */
static const unsigned int gappoh = 16;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 16;  /* vert outer gap between windows and screen edge */
static int smartgaps = 0;  /* 1 means no outer gap when there is only one window */
static const int swallowfloating = 0;  /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 4;  /* systray spacing */
static const int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;  /* 0 means no systray */
static const int user_bh = 20;  /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

/* colorscheme */
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title                    tags mask  isfloating  issticky  isterminal  noswallow  monitor */
	/* Floating */
	{ "Gnome-calculator",      NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },
	{ "Nitrogen",              NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },
	{ "Pavucontrol",           NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },
	{ "Blueman-manager",       NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },
	{ "Blueberry.py",          NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },
	{ "Nm-connection-editor",  NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },
	{ "flameshot",             NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },
	{ "photoshop.exe",         NULL,      NULL,                    0,         1,          0,        0,          0,         -1 },

	/* Floating and sticky */
	{ "mpv",                   NULL,      NULL,                    0,         1,          1,        0,          0,         -1 },
	{ NULL,                    NULL,      "Picture in picture",    0,         1,          1,        0,          0,         -1 },


	/* Swallow */
	{ "Alacritty",             NULL,      NULL,                    0,         0,          0,        1,          0,         -1 },
	{ "St",                    NULL,      NULL,                    0,         0,          0,        1,          0,         -1 },
	{ NULL,                    NULL,      "Event Tester",          0,         0,          0,        0,          1,         -1 },
	/* VIM shouldn't be swallowed when opening links. */
	{ "Brave-browser",         NULL,      NULL,                    0,         0,          0,        0,          1,         -1 },

	/* Tags */
	{ "Virt-manager",          NULL,      NULL,                    1 << 5,    0,          0,        0,           0,        -1 },
	{ "Virt-viewer",           NULL,      NULL,                    1 << 5,    0,          0,        0,           0,        -1 },
	{ "TelegramDesktop",       NULL,      NULL,                    1 << 6,    0,          0,        0,           0,        -1 },
	{ "WhatsAppQT",            NULL,      NULL,                    1 << 6,    0,          0,        0,           0,        -1 },
	{ "St",                    "cmus",    NULL,                    1 << 7,    0,          0,        0,           0,        -1 },
	{ "Spotify",               NULL,      NULL,                    1 << 7,    0,          0,        0,           0,        -1 },
	{ "St",                    "sys",     NULL,                    1 << 8,    0,          0,        0,           0,        -1 },
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;  /* number of clients in master area */
static int resizehints = 1;  /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_g,     ACTION##stack, {.i = 0 } }, \
	//{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	//{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	//{ MOD, XK_x,     ACTION##stack, {.i = -1 } },
	//{ MOD, XK_q,     ACTION##stack, {.i = 0 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* [> component of dmenucmd, manipulated in spawn() <] */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[] = { "/bin/sh", "-c", "$TERMINAL", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "105x30",  NULL };
static const char *volup[] = { "/bin/sh", "-c",  "volume up", NULL };
static const char *voldown[] = { "/bin/sh", "-c",  "volume down", NULL };
static const char *mute[] = { "/bin/sh", "-c",  "volume mute", NULL };
static const char *player_prev[] = { "/bin/sh", "-c", "playerctl previous && sleep 0.5 && dwmbar", NULL };
static const char *player_next[] = { "/bin/sh", "-c", "playerctl next && sleep 0.5 && dwmbar", NULL };
static const char *player_pause[] = { "/bin/sh", "-c", "playerctl play-pause && sleep 0.5 && dwmbar", NULL };
static const char *player_stop[] = { "/bin/sh", "-c", "playerctl stop && sleep 0.5 && dwmbar", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{ "font",               STRING,  &font },
	{ "dmenufont",          STRING,  &dmenufont },
	{ "normbgcolor",        STRING,  &normbgcolor },
	{ "normbordercolor",    STRING,  &normbordercolor },
	{ "normfgcolor",        STRING,  &normfgcolor },
	{ "selbgcolor",         STRING,  &selbgcolor },
	{ "selbordercolor",     STRING,  &selbordercolor },
	{ "selfgcolor",         STRING,  &selfgcolor },
	{ "borderpx",           INTEGER, &borderpx },
	{ "snap",               INTEGER, &snap },
	{ "showbar",            INTEGER, &showbar },
	{ "topbar",             INTEGER, &topbar },
	{ "nmaster",            INTEGER, &nmaster },
	{ "resizehints",        INTEGER, &resizehints },
	{ "mfact",              FLOAT,   &mfact },
};

static Key keys[] = {
	/* modifier                     key                      function        argument */
	STACKKEYS(MODKEY,                                        focus)
	STACKKEYS(MODKEY|ShiftMask,                              push)
	{ MODKEY,                       XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,               togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_Escape,               spawn,          SHCMD("slock") },
	{ MODKEY|ShiftMask,             XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_bracketright,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,          incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,                zoom,           {0} },
	{ MODKEY,                       XK_z,                    view,           {0} },
	{ MODKEY|ShiftMask,             XK_z,                    spawn,          SHCMD("flash-window") },
	{ MODKEY,                       XK_q,                    killclient,     {0} },
	{ MODKEY,                       XK_comma,                cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_s,                    togglesticky,   {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY|Mod1Mask,              XK_w,                    spawn,          SHCMD("qimgv $WALLPAPERS") },

	/* Layouts */
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} }, // tiling
	{ MODKEY|ShiftMask,             XK_t,                    setlayout,      {.v = &layouts[13]} }, // floating
	{ MODKEY,                       XK_y,                    setlayout,      {.v = &layouts[1]} }, // monocle
	{ MODKEY|ShiftMask,             XK_y,                    setlayout,      {.v = &layouts[4]} }, // deck
	{ MODKEY,                       XK_i,                    setlayout,      {.v = &layouts[2]} }, // spiral
	{ MODKEY|ShiftMask,             XK_i,                    setlayout,      {.v = &layouts[3]} }, // dwindle
	{ MODKEY,                       XK_u,                    setlayout,      {.v = &layouts[11]} }, // centeredmaster
	{ MODKEY|ShiftMask,             XK_u,                    setlayout,      {.v = &layouts[12]} }, // centeredfloatingmaster

	/* Gaps */
	{ MODKEY,                       XK_equal,                incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,                incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,                defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_minus,                togglegaps,     {0} },
	//{ MODKEY|Mod4Mask,              XK_i,                    incrigaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_i,                    incrigaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_o,                    incrogaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_o,                    incrogaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_6,                    incrihgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_6,                    incrihgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_7,                    incrivgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_7,                    incrivgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_8,                    incrohgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_8,                    incrohgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_9,                    incrovgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_9,                    incrovgaps,     {.i = -1 } },

	/* dmenu */
	/* This --dmenu option brings commands on PATH, as per j4-dmenu-desktop documentation. */
	/* Not passing --no-generic shows both generic name and application name. */
	{ MODKEY,                       XK_d,                    spawn,          SHCMD("j4-dmenu-desktop --no-generic --term=\"$TERMINAL\" --dmenu=\"(cat ; (stest -flx $(echo $PATH | tr : ' ') | sort -u)) | dmenu -l 6 -g 9\"") },
	{ Mod1Mask|ControlMask,         XK_Delete,               spawn,          SHCMD("dmenu_power") },

	/* Audio */
	{ 0,                            XF86XK_AudioMute,        spawn,          {.v = mute } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = voldown } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = volup } },
	{ 0,                            XF86XK_AudioPrev,        spawn,          {.v = player_prev } },
	{ 0,                            XF86XK_AudioNext,        spawn,          {.v = player_next } },
	{ 0,                            XF86XK_AudioPlay,        spawn,          {.v = player_pause } },
	{ 0,                            XF86XK_AudioStop,        spawn,          {.v = player_stop } },

	TAGKEYS(                        XK_1,                    0)
	TAGKEYS(                        XK_2,                    1)
	TAGKEYS(                        XK_3,                    2)
	TAGKEYS(                        XK_4,                    3)
	TAGKEYS(                        XK_5,                    4)
	TAGKEYS(                        XK_6,                    5)
	TAGKEYS(                        XK_7,                    6)
	TAGKEYS(                        XK_8,                    7)
	TAGKEYS(                        XK_9,                    8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button2,        killclient,     {0} },
	{ ClkWinTitle,          0,              Button3,        spawn,          SHCMD("nemo") },
	{ ClkStatusText,        0,              Button1,        spawn,          SHCMD("zenity --calendar") },
	{ ClkStatusText,        0,              Button9,        spawn,          {.v = player_next } },
	{ ClkStatusText,        0,              Button8,        spawn,          {.v = player_prev } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = player_pause } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = volup } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = voldown } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

