/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 18;       /* gap pixel between windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_bg[]          = "#181818";
static const char col_dgray[]       = "#585858";
static const char col_fg[]          = "#d8d8d8";
static const char col_red[]         = "#ab4642";
static const char col_yellow[]      = "#f7ca88";
static const char *colors[][3]      = {
	/*               fg             bg              border   */
	[SchemeNorm]   = { col_dgray,   col_bg,         col_bg },
	[SchemeSel]    = { col_fg,      col_bg,         col_dgray },
	[SchemeWarn]   = { col_yellow,  col_bg,         col_yellow },
	[SchemeUrgent] = { col_red,     col_bg,         col_red },
 };

/* tagging */
static const char *tags[] = { "term", "web", "com", "media", "file", "misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tags mask     isfloating   monitor */
        { "feh",         NULL,       NULL,       0,            1,           -1 },
	{ "qutebrowser", NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Zathura",     NULL,       NULL,       1 << 4,       0,           -1 },
        { "mpv",         NULL,       NULL,       1 << 3,       0,           -1 },
        { "st-256color", NULL,       "vifm",     1 << 4,       0,           -1 },
        { "st-256color", NULL,       "ncmpcpp",  1 << 3,       0,           -1 },
        { "st-256color", NULL,       "mutt",     1 << 2,       0,           -1 },
        { "st-256color", NULL,       "w3m",      1 << 1,       0,           -1 },
 };

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]    = { "st", NULL };
static const char *dmenucmd[]   = { "dm", NULL };
static const char *searchraw[]  = { "dm_sr", NULL };
static const char *passstore[]  = { "dm_pass", NULL };
static const char *mousemove[]  = { "mousemove", NULL};
static const char *volupcmd[]   = { "pacontrol", "up", NULL };
static const char *voldncmd[]   = { "pacontrol", "down", NULL };
static const char *handleurl[]     = { "urlhandler", NULL };
static const char *mpcstop[]       = { "mpc", "stop", NULL };
static const char *mpctog[]        = { "mpc", "toggle", NULL };
static const char *mpcprev[]       = { "mpc", "prev", NULL };
static const char *mpcnext[]       = { "mpc", "next", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_o,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
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
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
        { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
        { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mousemove } },
        { MODKEY,                       XK_p,      spawn,          {.v = passstore } },
        { MODKEY,                       XK_s,      spawn,          {.v = searchraw } },
        { MODKEY,                       XK_minus,  spawn,          {.v = volupcmd } },
        { MODKEY|ShiftMask,             XK_minus,  spawn,          {.v = voldncmd } },
        { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = handleurl } },
        { MODKEY,                       XK_slash,  spawn,          {.v = mpctog } },
        { MODKEY|ShiftMask,             XK_slash,  spawn,          {.v = mpcstop } },
        { MODKEY,                       XK_Left,   spawn,          {.v = mpcprev } },
        { MODKEY,                       XK_Right,  spawn,          {.v = mpcnext } },
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

