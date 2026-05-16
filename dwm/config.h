/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 6;        /* gap between windows */
static const int vertpadbar         = 6;        /* vertical padding added to bar height */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const unsigned int externalsystraywidth = 104;
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor */
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"Spleen:pixelsize=24",
	"SpaceMono Nerd Font:size=11",
	"Noto Sans CJK JP:size=11",
	"monospace:size=11",
};
static const char dmenufont[]       = "Spleen:pixelsize=24";
static const char col_bg[]          = "#1f2430";
static const char col_bg_alt[]      = "#252b38";
static const char col_fg[]          = "#cbccc6";
static const char col_dim[]         = "#707a8c";
static const char col_accent[]      = "#87d96c";
static const char col_occupied[]    = "#f28779";
static const char *colors[][3]      = {
	/*               fg            bg          border     */
	[SchemeNorm] = { col_fg,       col_bg,     col_dim    },
	[SchemeSel]  = { col_accent,   col_bg_alt, col_accent },
	[SchemeOcc]  = { col_occupied, col_bg,     col_dim    },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class         instance  title  tags mask  isfloating  monitor */
	{ "Gimp",        NULL,     NULL,  0,         1,          -1 },
	{ "Pavucontrol", NULL,     NULL,  0,         1,          -1 },
	{ "float",       NULL,     NULL,  0,         1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 144;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run", "-m", dmenumon, "-fn", dmenufont,
	"-nb", col_bg, "-nf", col_fg, "-sb", col_bg_alt, "-sf", col_accent,
	NULL
};
static const char *termcmd[]     = { "st", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *musiccmd[]    = { "st", "-e", "ncmpcpp", NULL };
static const char *ytcmd[]       = { "yt", NULL };
static const char *lockcmd[]     = { "slock", NULL };
static const char *exitcmd[]     = { "exit-menu", NULL };
static const char *wallcmd[]     = { "wall", "menu", NULL };
static const char *shotcmd[]     = { "screenshot", "menu", NULL };
static const char *shotareacmd[] = { "screenshot", "area", NULL };
static const char *shotfullcmd[] = { "screenshot", "full", NULL };
static const char *volupcmd[]    = { "volume", "up", NULL };
static const char *voldncmd[]    = { "volume", "down", NULL };
static const char *volmutecmd[]  = { "volume", "mute", NULL };
static const char *micmutecmd[]  = { "volume", "mic", NULL };
static const char *brightupcmd[] = { "brightness", "up", NULL };
static const char *brightdncmd[] = { "brightness", "down", NULL };
static const char *playcmd[]     = { "music-control", "toggle", NULL };
static const char *nextcmd[]     = { "music-control", "next", NULL };
static const char *prevcmd[]     = { "music-control", "prev", NULL };
static const char *stopcmd[]     = { "music-control", "stop", NULL };

static const char *statuscmds[] = {
	[0] = NULL,
	[1] = "sb-clock",
	[2] = "sb-battery",
	[3] = "sb-volume",
	[4] = "sb-network",
	[5] = "sb-bluetooth",
	[6] = "sb-music",
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },
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
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = exitcmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = musiccmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = micmutecmd } },
	{ MODKEY,                       XK_y,      spawn,          {.v = ytcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = wallcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = shotareacmd } },
	{ 0,                            XK_Print,  spawn,          {.v = shotfullcmd } },
	{ ShiftMask,                    XK_Print,  spawn,          {.v = shotcmd } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldncmd } },
	{ 0,                            XF86XK_AudioMute,        spawn, {.v = volmutecmd } },
	{ 0,                            XF86XK_AudioMicMute,     spawn, {.v = micmutecmd } },
	{ 0,                            XF86XK_MonBrightnessUp,  spawn, {.v = brightupcmd } },
	{ 0,                            XF86XK_MonBrightnessDown,spawn, {.v = brightdncmd } },
	{ 0,                            XF86XK_AudioPlay,        spawn, {.v = playcmd } },
	{ 0,                            XF86XK_AudioNext,        spawn, {.v = nextcmd } },
	{ 0,                            XF86XK_AudioPrev,        spawn, {.v = prevcmd } },
	{ 0,                            XF86XK_AudioStop,        spawn, {.v = stopcmd } },
};

static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        statusclick,    {0} },
	{ ClkStatusText,        0,              Button2,        statusclick,    {0} },
	{ ClkStatusText,        0,              Button3,        statusclick,    {0} },
	{ ClkStatusText,        0,              Button4,        statusclick,    {0} },
	{ ClkStatusText,        0,              Button5,        statusclick,    {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
