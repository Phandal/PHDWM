/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 11;       /* vertical padding for statusbar */
static const char *fonts[]          = { "CaskaydiaCove Nerd Font Mono:size=10" };
static const char dmenufont[]       = "CaskaydiaCove Nerd Font Mono:size=10";
static const char col_gray1[]       = "#EEE8D5";
static const char col_gray2[]       = "#93A1A1";
static const char col_gray3[]       = "#586E75";
static const char col_white[]       = "#839496";
static const char col_gray4[]       = "#657B83";
static const char col_cyan[]        = "#2AA198";
static const char col_frost[]       = "#93A1A1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_gray1, col_gray1 },
	[SchemeSel]  = { col_white, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
  "unclutter", NULL,
	"picom", NULL,
	"/home/bailey/.fehbg", NULL,
	"xset", "r", "rate", "300", "30", NULL,
	"dunst", NULL,
	"emacs", "--daemon", NULL,
	"mopidy", NULL,
	"/home/bailey/.config/PHDWM/bar/bar.sh", NULL,
	"mopidy", NULL,
  "redshift", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "ﭮ", "" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const char *tagsel[][2] = {
	{ "#2AA198", "#FDf6E3" },
	{ "#DC322F", "#FDf6E3" },
	{ "#CB4B16", "#FDf6E3" },
	{ "#B58900", "#FDf6E3" },
	{ "#859900", "#FDf6E3" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "discord",  NULL,       NULL,       1 << 3,       0,            1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, 
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
	{ "G",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_white, "-sb", col_cyan, "-sf", col_white, NULL };
static const char *termcmd[]  = { "st", NULL };

/* Custom Commands */
static const char *browsercmd[] = { "firefox", NULL };
static const char *editorcmd[] = { "emacsclient", "-n", "-c", NULL };
static const char *roficmd[] = { "rofi", "-m", "-4", "-show", "drun", NULL };
static const char *upvolcmd[] = { "pamixer", "--increase", "5", NULL };
static const char *downvolcmd[] = { "pamixer", "--decrease", "5", NULL };
static const char *mutevolcmd[] = { "pamixer", "-t", NULL };
static const char *nextsongcmd[] = { "playerctl", "next", NULL };
static const char *prevsongcmd[] = { "playerctl", "previous", NULL };
static const char *togglesongcmd[] = { "playerctl," "play-pause", NULL };
static const char *sleepcmd[] = { "slock", "systemctl", "suspend", "-i", NULL };
static const char *rofipowercmd[] = { "rofipower", NULL };
static const char *notifcmd[] = { "notifToggle", NULL };
static const char *prntsccmd[] = { "selScreenshot", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
        { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
  
  /* Custom Keybinds */
  { MODKEY,                       XK_e,                      spawn,          {.v = editorcmd } },
	{ MODKEY,                       XK_b,                      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_l,                      spawn,          {.v = sleepcmd } },
	{ MODKEY,                       XK_r,                      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_q,                      spawn,          {.v = rofipowercmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = upvolcmd } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = downvolcmd } },
	{ 0,                            XF86XK_AudioMute,          spawn,          {.v = mutevolcmd } },
	{ 0,                            XF86XK_AudioNext,          spawn,          {.v = nextsongcmd } },
	{ 0,                            XF86XK_AudioPrev,          spawn,          {.v = prevsongcmd } },
	{ 0,                            XF86XK_AudioPlay,          spawn,          {.v = togglesongcmd } },
	{ MODKEY,                       XK_n,                      spawn,          {.v = notifcmd } },
	{ 0,                            XK_Print,                  spawn,          {.v = prntsccmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

