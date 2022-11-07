/*  ____ _____  */
/* |  _ \_   _|  Derek Taylor (DistroTube) */
/* | | | || |  	http://www.youtube.com/c/DistroTube */
/* | |_| || |  	http://www.gitlab.com/dtos/etc/dtos-distrotube */
/* |____/ |_|  	*/

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel/.config/polybar/launch.sh */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/.config/polybar/launch.sh"; /* Alternate bar launch command */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 8;        /* vertical padding for statusbar */
/* Default font will be Ubuntu if installed (ttf-ubuntu).
 * Otherwise, your default font will be Hack (ttf-hack)
 * JoyPixels (ttf-joypixels) is a dependency for colored fonts and emojis.
 */
static const char *fonts[]     = {"Hack:size=8:antialias=true:autohint=true",
                                  "Noto Sans:size=10:antialias=true:autohint=true"
						     	};

static const char col_1[]  = "#282c34"; /* background color of bar */
static const char col_2[]  = "#282c34"; /* border color unfocused windows */
static const char col_3[]  = "#d7d7d7";
static const char col_4[]  = "#924441"; /* border color focused windows and tags */
/* bar opacity
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * 0xdd adds adds a bit more transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha    = 0xff;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_4, col_4 },
};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
/* static const char *tags[] = { "", "", "", "", "", "", "", "", "" }; */
static const char *tags[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "grid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG)												\
	{1, {{MODKEY, KEY}},								view,           {.ui = 1 << TAG} },	\
	{1, {{MODKEY|ControlMask, KEY}},					toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},						tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},			toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]    = { "alacritty", NULL };
static const char *trayercmd[]  = { "trayer", "--edge", "top", "--align", "center", "--widthtype", "request", "--padding", "7", "--SetDockType", "true", "--SetPartialStrut", "false", "--expand", "true", "--monitor", "0", "--transparent", "true", "--alpha", "0", "--tint", "0x924441", "--height", "17", NULL };

static Keychord keychords[] = {
	/* Keys                              function         argument */
	{1, {{MODKEY|ShiftMask, XK_Return}}, spawn,           SHCMD("~/.local/bin/launch_rofi.sh") },
	{1, {{MODKEY|ShiftMask, XK_l}},		 spawn,           SHCMD("betterlockscreen --lock") },
	{1, {{MODKEY, XK_Return}},			 spawn,           {.v = termcmd } },
	{1, {{MODKEY|ShiftMask, XK_c}},		 killclient,      {0} },

    /* Web browsers */
    {1, {{MODKEY, XK_b}},                 spawn,          SHCMD("google-chrome") },

	/* Emacs */
    {1, {{MODKEY, XK_e}},                 spawn,          SHCMD("emacs") },

	/* System tray */
    {1, {{MODKEY, XK_semicolon}},           spawn,        {.v = trayercmd } },
    {1, {{MODKEY|ShiftMask, XK_semicolon}}, spawn,        SHCMD("killall trayer") },

	{1, {{MODKEY|ShiftMask, XK_b}},		  togglebar,      {0} },
	{1, {{MODKEY, XK_j}},				  focusstack,     {.i = +1 } },
	{1, {{MODKEY, XK_k}},				  focusstack,     {.i = -1 } },
	{1, {{MODKEY|ShiftMask, XK_j}},		  rotatestack,    {.i = +1 } },
	{1, {{MODKEY|ShiftMask, XK_k}},		  rotatestack,    {.i = -1 } },
	{1, {{MODKEY, XK_i}},				  incnmaster,     {.i = +1 } },
	{1, {{MODKEY, XK_d}},				  incnmaster,     {.i = -1 } },
	{1, {{MODKEY, XK_h}},				  setmfact,       {.f = -0.05} },
	{1, {{MODKEY, XK_l}},				  setmfact,       {.f = +0.05} },
	{1, {{MODKEY, XK_z}},   			  zoom,           {0} },
	{1, {{MODKEY, XK_v}},				  view,           {0} },

    /* Layout manipulation */
	{1, {{MODKEY, XK_t}},				  setlayout,      {.v = &layouts[0]} },
	{1, {{MODKEY, XK_f}},				  setlayout,      {.v = &layouts[1]} },
	{1, {{MODKEY, XK_m}},   		      setlayout,      {.v = &layouts[2]} },
	{1, {{MODKEY, XK_g}},				  setlayout,      {.v = &layouts[3]} },
	{1, {{MODKEY, XK_space}},	          togglefullscr,  {0} },
	{1, {{MODKEY|ShiftMask, XK_f}},	      togglefloating, {0} },

	{1, {{ MODKEY, XK_Tab}},              cyclelayout,    {.i = -1 } },
	{1, {{ MODKEY|ShiftMask, XK_Tab}},    cyclelayout,    {.i = +1 } },

	{1, {{MODKEY, XK_0}},				  view,           {.ui = ~0 } },
	{1, {{MODKEY|ShiftMask, XK_0}},		  tag,            {.ui = ~0 } },

    /* Switching between monitors */
	{1, {{MODKEY, XK_comma}},			  focusmon,       {.i = -1 } },
	{1, {{MODKEY, XK_period}},			  focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask, XK_comma}},	  tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask, XK_period}},  tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

    /* Restart or quit dwm */
	{1, {{MODKEY|ShiftMask, XK_r}},		  quit,           {1} },
	{1, {{MODKEY|ShiftMask, XK_q}},		  quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

