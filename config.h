/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int gappih = 10;  /* horiz inner gap between windows */
static const unsigned int gappiv = 10;  /* vert inner gap between windows */
static const unsigned int gappoh =
    10; /* horiz outer gap between windows and screen edges */
static const unsigned int gappov =
    10; /* horiz outer gap between windows and screen edges */
static const int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
// static const char *fonts[]          = {"JetBrainsMono Nerd Font
// Mono:pixelsize=12:antialias=true:autohint=true"}; static const char
// dmenufont[]       = "JetBrainsMono Nerd Font
// Mono:pixelsize=12:antialias=true:autohint=true";
static const char *fonts[] = {
    "Iosevka NFM:pixelsize=13:antialias=true:autohint=true"};
static const char dmenufont[] =
    "Iosevka NFM:pixelsize=13:antialias=true:autohint=true";
// #### NORD ####
// static const char col_gray1[]       = "#3B4252";
// static const char col_gray2[]       = "#4C566A";
// static const char col_gray3[]       = "#E5E9F0";
// static const char col_gray4[]       = "#4C566A";
// static const char col_cyan[]        = "#8FBCBB";

// #### GRUVBOX ####
static const char col_gray1[] = "#282828";
static const char col_gray2[] = "#504945";
static const char col_gray3[] = "#EBDBB2";
static const char col_gray4[] = "#504945";
static const char col_cyan[] = "#B8BB26";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray1},
    [SchemeSel] = {col_gray3, col_gray4, col_gray4},
};

/* tagging */
static const char *tags[] = {"", "", "", "󰒱", "", "󰇮", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                       instance    title       tags mask isfloating
       monitor */
    // { "Gimp",                   NULL,       NULL,       0,            1, -1
    // }, { "Firefox",                NULL,       NULL,       1 << 8,       0,
    // -1 },
    {"Microsoft Teams - Preview", NULL, NULL, 8, 0, 1},
    {"Slack", NULL, NULL, 8, 0, 0},
    {"crx_pkooggnaalmfkidjmlhoelhdllpphaga", NULL, NULL, 3, 0, 1},
    {"discord", NULL, NULL, 2, 0, 1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},        {"###", gaplessgrid},
    {"|M|", centeredmaster}, {">M>", centeredfloatingmaster},
    {"|||", threecolumn},
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask

#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static const char *dmenucmd[] = {"dmenu_run", "-fn", dmenufont, "-nb",
                                 col_gray1,   "-nf", col_gray3, "-sb",
                                 col_gray2,   "-sf", col_gray3, NULL};
static const char *termcmd[] = {"st", NULL};
static const char *browsercmd[] = {"google-chrome-stable", NULL};
static const char *editorcmd[] = {"emacsclient", "-n", "-c", NULL};
// static const char *screenshotcmd[] = { "maim", "-s", "-u", "|", "tee",
// "~/Downloads/$(date +%s).png", "|", "xclip", "-selection", "clipboard", "-t",
// "image/png", NULL };
static const char *screenshotcmd[] = {"shot", NULL};
static const char *screenshotsavecmd[] = {"shot_save", NULL};
static const char *volumeupcmd[] = {"pamixer", "-i", "2", NULL};
static const char *volumedowncmd[] = {"pamixer", "-d", "2", NULL};
static const char *volumemutecmd[] = {"pamixer", "-t", NULL};
static const char *nextsongcmd[] = {"playerctl", "--player=spotify", "next",
                                    NULL};
static const char *prevsongcmd[] = {"playerctl", "--player=spotify", "previous",
                                    NULL};
static const char *playsongcmd[] = {"playerctl", "--player=spotify",
                                    "play-pause", NULL};
static const char *donotdisturbcmd[] = {"donotdisturb", NULL};
static const char *filebrowsercmd[] = {"pcmanfm", NULL};

static const Key keys[] = {
    /* modifier                 key                       function argument */
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volumeupcmd}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = volumedowncmd}},
    {0, XF86XK_AudioMute, spawn, {.v = volumemutecmd}},
    {0, XF86XK_AudioNext, spawn, {.v = nextsongcmd}},
    {0, XF86XK_AudioPrev, spawn, {.v = prevsongcmd}},
    {0, XF86XK_AudioPlay, spawn, {.v = playsongcmd}},
    {0, XK_Print, spawn, {.v = screenshotcmd}},
    {ShiftMask, XK_Print, spawn, {.v = screenshotsavecmd}},
    {MODKEY, XK_e, spawn, {.v = editorcmd}},
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_b, spawn, {.v = browsercmd}},
    {MODKEY | ShiftMask, XK_f, spawn, {.v = filebrowsercmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_k, setcfact, {.f = +0.25}},
    {MODKEY | ShiftMask, XK_j, setcfact, {.f = -0.25}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = +0.00}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[5]}},
    {MODKEY | ShiftMask, XK_g, setlayout, {.v = &layouts[6]}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask        button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkWinTitle, MODKEY, Button1, spawn, {.v = donotdisturbcmd}},
    {ClkStatusText, 0, Button2, spawn, {.v = volumemutecmd}},
    {ClkStatusText, 0, Button4, spawn, {.v = volumeupcmd}},
    {ClkStatusText, 0, Button5, spawn, {.v = volumedowncmd}},
    {ClkStatusText, MODKEY, Button1, spawn, {.v = prevsongcmd}},
    {ClkStatusText, MODKEY, Button3, spawn, {.v = nextsongcmd}},
    {ClkStatusText, MODKEY, Button2, spawn, {.v = playsongcmd}},
    {ClkClientWin, MODKEY, Button1, dragmfact, {0}},
    {ClkClientWin, MODKEY, Button3, dragcfact, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY | ShiftMask, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY | ShiftMask, Button1, movemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
