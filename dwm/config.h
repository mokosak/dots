#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"

static unsigned int borderpx  = 3;
static unsigned int snap      = 32;
static unsigned int gappih    = 12;
static unsigned int gappiv    = 12;
static unsigned int gappoh    = 6;
static unsigned int gappov    = 6;
static int swallowfloating    = 0;
static int smartgaps          = 0;
static int showbar            = 1;
static int topbar             = 1;
static char *fonts[]          = {
	"Iosevka:size=12",
	"Noto Color Emoji:pixelsize=12:antialias=true:autohint=true",
};
static char normbgcolor[]           = "#1d2021";
static char normbordercolor[]       = "#282828";
static char normfgcolor[]           = "#ebdbb2";
static char selfgcolor[]            = "#1d2021";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#98971a";
static char titlefgcolor[]          = "#ebdbb2";
static char titlebgcolor[]          = "#3c3836";
static char *colors[][3] = {
       [SchemeNorm]  = { normfgcolor,  normbgcolor,  normbordercolor },
       [SchemeSel]   = { selfgcolor,   selbgcolor,   selbordercolor  },
       [SchemeTitle] = { titlefgcolor, titlebgcolor, titlebgcolor    },
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,          1 << 8,      0,           0,          0,         -1 },
	{ TERMCLASS,  NULL,       NULL,       	 0,           0,           1,          0,         -1 },
	{ NULL,       NULL,       "Event Tester", 0,          0,           0,          1,         -1 },
	{ TERMCLASS,  "floatterm", NULL,       	 0,           1,           1,          0,         -1 },
	{ TERMCLASS,  "bg",        NULL,       	 1 << 7,      0,           1,          0,         -1 },
};

static float mfact     = 0.55;
static int nmaster     = 1;
static int resizehints = 0;
static const int lockfullscreen = 1;
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	{ "[]=",	tile },
	{ "><>",	NULL },
	{ "[M]",	monocle },
	{ "|M|",	centeredmaster },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char *termcmd[]  = { TERMINAL, NULL };

#define VOLUME(args)     SHCMD("wpctl " args "; pkill -RTMIN+12 dwmblocks")
#define BRIGHTNESS(step) SHCMD("brightnessctl -q set " step "; pkill -RTMIN+20 dwmblocks")

ResourcePref resources[] = {
		{ "normbgcolor",	STRING,	&normbgcolor },
		{ "normbordercolor",	STRING,	&normbordercolor },
		{ "normfgcolor",	STRING,	&normfgcolor },
		{ "selbgcolor",		STRING,	&selbgcolor },
		{ "selbordercolor",	STRING,	&selbordercolor },
		{ "selfgcolor",		STRING,	&selfgcolor },
		{ "titlebgcolor",	STRING,	&titlebgcolor },
		{ "titlefgcolor",	STRING,	&titlefgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>

static const Key keys[] = {
	{ MODKEY,			XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY,			XK_d,          spawn,                  {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY,			XK_b,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,			XK_m,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ MODKEY,			XK_r,          spawn,                  {.v = (const char*[]){ "thunar", NULL } } },
	{ MODKEY,			XK_n,          spawn,                  SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_w,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "nmtui", NULL } } },
	{ MODKEY,			XK_x,          spawn,                  {.v = (const char*[]){ "slock", NULL } } },
	{ MODKEY|ShiftMask,		XK_e,          spawn,                  {.v = (const char*[]){ "sysact", NULL } } },

	{ 0,				XK_Print,      spawn,                  {.v = (const char*[]){ "maimpick", "full", NULL } } },
	{ MODKEY|ShiftMask,		XK_s,          spawn,                  {.v = (const char*[]){ "maimpick", "area", NULL } } },
	{ ShiftMask,			XK_Print,      spawn,                  {.v = (const char*[]){ "maimpick", NULL } } },

	{ MODKEY,			XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,			XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,			XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,			XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,			XK_o,          incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,          incnmaster,             {.i = -1 } },
	{ MODKEY,			XK_z,          zoom,                   {0} },
	{ MODKEY,			XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,		XK_q,          quit,                   {0} },
	{ MODKEY|ShiftMask,		XK_f,          togglefullscr,          {0} },
	{ MODKEY|ShiftMask,		XK_space,      togglefloating,         {0} },
	{ MODKEY,			XK_s,          togglesticky,           {0} },
	{ MODKEY|ShiftMask,		XK_b,          togglebar,              {0} },

	{ MODKEY,			XK_space,      setlayout,              {0} },
	{ MODKEY,			XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,			XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,			XK_u,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,			XK_i,          setlayout,              {.v = &layouts[3]} },

	TAGKEYS(			XK_1,          0)
	TAGKEYS(			XK_2,          1)
	TAGKEYS(			XK_3,          2)
	TAGKEYS(			XK_4,          3)
	TAGKEYS(			XK_5,          4)
	TAGKEYS(			XK_6,          5)
	TAGKEYS(			XK_7,          6)
	TAGKEYS(			XK_8,          7)
	TAGKEYS(			XK_9,          8)
	{ MODKEY,			XK_0,	       view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,	       tag,                    {.ui = ~0 } },
	{ MODKEY,			XK_Tab,        view,                   {0} },
	{ MODKEY,			XK_Left,       focusmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,       tagmon,                 {.i = -1 } },
	{ MODKEY,			XK_Right,      focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,      tagmon,                 {.i = +1 } },

	{ MODKEY,			XK_minus,      spawn,                  VOLUME("set-mute @DEFAULT_AUDIO_SINK@ 0; wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%-") },
	{ MODKEY,			XK_equal,      spawn,                  VOLUME("set-mute @DEFAULT_AUDIO_SINK@ 0; wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%+") },
	{ MODKEY|ShiftMask,		XK_m,          spawn,                  VOLUME("set-mute @DEFAULT_AUDIO_SOURCE@ toggle") },
	{ MODKEY,			XK_p,          spawn,                  {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ MODKEY,			XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ MODKEY,			XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "next", NULL } } },

	{ 0, XF86XK_AudioMute,                         spawn,                  VOLUME("set-mute @DEFAULT_AUDIO_SINK@ toggle") },
	{ 0, XF86XK_AudioRaiseVolume,                  spawn,                  VOLUME("set-mute @DEFAULT_AUDIO_SINK@ 0; wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%+") },
	{ 0, XF86XK_AudioLowerVolume,                  spawn,                  VOLUME("set-mute @DEFAULT_AUDIO_SINK@ 0; wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%-") },
	{ 0, XF86XK_AudioMicMute,                      spawn,                  VOLUME("set-mute @DEFAULT_AUDIO_SOURCE@ toggle") },
	{ 0, XF86XK_AudioPlay,                         spawn,                  {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ 0, XF86XK_AudioPause,                        spawn,                  {.v = (const char*[]){ "mpc", "pause", NULL } } },
	{ 0, XF86XK_AudioStop,                         spawn,                  {.v = (const char*[]){ "mpc", "stop", NULL } } },
	{ 0, XF86XK_AudioPrev,                         spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ 0, XF86XK_AudioNext,                         spawn,                  {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,                   spawn,                  BRIGHTNESS("5%+") },
	{ 0, XF86XK_MonBrightnessDown,                 spawn,                  BRIGHTNESS("5%-") },
};

static const Button buttons[] = {
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
#ifndef __OpenBSD__
	{ ClkStatusText,        0,                   Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,                   Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,                   Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,                   Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,                   Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,           Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
	{ ClkRootWin,		0,		     Button2,	     togglebar,      {0} },
};
