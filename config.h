/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
   "DejaVuSans Mono:size=12"
};
static const char dmenufont[]       = "DejaVuSans Mono:size=12";
static const char normbordercolor[] = "#181818";
static const char normbgcolor[]     = "#181818";
static const char normfgcolor[]     = "#585858";
static const char selbordercolor[]  = "#585858";
static const char selbgcolor[]      = "#181818";
static const char selfgcolor[]      = "#D8D8D8";
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 18;       /* gap pixel between windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* statuscolors */
#define NUMCOLORS 4
static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  // border   foreground background
  { "#181818", "#585858", "#181818" },  // normal
  { "#585858", "#D8D8D8", "#181818" },  // selected
  { "#AB4642", "#AB4642", "#181818" },  // urgent/warning  (black on yellow)
  { "#181818", "#F7CA88", "#181818" },  // occupied 
  // add more here
};

/* tagging */
static const char *tags[] = { "term", "web", "mail", "music", "video", "file", "misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor */
	{ "feh",          NULL,       NULL,       0,            1,           -1 },
	{ "qutebrowser",  NULL,       NULL,       1 << 1,       0,           -1 },
        { "Zathura",      NULL,       NULL,       1 << 5,       0,           -1 },
        { "nautilus",     NULL,       NULL,       1 << 5,       1            -1 },
        { "mpv",          NULL,       NULL,       1 << 4,       0,           -1 },
        { "st-256color",  NULL,       "ncmpcpp",  1 << 3,       0,           -1 },
        { "st-256color",  NULL,       "ncmpcpp",  1 << 3,       0,           -1 },
        { "st-256color",  NULL,       "mutt",     1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "bstack.c"
#include "gaplessgrid.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
  { "[B]",      bstack, },
  { "[G]",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      view,                 {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,                  {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,            {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char scratchpadname[] = "scratchpad";
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/*static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };*/
static const char *termcmd[]       = { "st", NULL };
static const char *dmenucmd[]      = { "dm", NULL };
static const char *browser[]       = { "qutebrowser", NULL, "qutebrowser"};
static const char *volupcmd[]      = { "dmixer", "up", NULL };
static const char *voldncmd[]      = { "dmixer", "down", NULL };
static const char *mpcstop[]       = { "mpc", "stop", NULL };
static const char *mpctog[]        = { "mpc", "toggle", NULL };
static const char *mpcprev[]       = { "mpc", "prev", NULL };
static const char *mpcnext[]       = { "mpc", "next", NULL };
static const char *playgood[]      = { "goodsong", "-p", NULL };
static const char *addgood[]       = { "goodsong", NULL };
static const char *searchraw[]     = { "dm_sr", NULL };
static const char *mousemove[]     = { "swarp", "0", "1440", NULL};
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "push.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_o,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browser } },
	{ MODKEY,                       XK_minus,  spawn,          {.v = volupcmd } },
        { MODKEY|ShiftMask,             XK_minus,  spawn,          {.v = voldncmd } },
        { MODKEY,                       XK_Up,     spawn,          {.v = playgood } },
        { MODKEY|ShiftMask,             XK_Up,     spawn,          {.v = addgood } },
        { MODKEY,                       XK_slash,  spawn,          {.v = mpctog } },
        { MODKEY|ShiftMask,             XK_slash,  spawn,          {.v = mpcstop } },
        { MODKEY,                       XK_Left,   spawn,          {.v = mpcprev } },
        { MODKEY,                       XK_Right,  spawn,          {.v = mpcnext } },
        { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mousemove } },
        { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = searchraw } },
        { MODKEY,                       XK_s,      togglescratch,  {.v = scratchpadcmd } },
        { MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
        { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
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
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

