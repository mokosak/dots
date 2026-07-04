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
static char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"  };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
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
	/* symbol     arrange function */
	{ "[]=",	tile },	                /* Default: Master on left, slaves on right */
	{ "TTT",	bstack },               /* Master on top, slaves on bottom */

	{ "[@]",	spiral },               /* Fibonacci spiral */
	{ "[\\]",	dwindle },              /* Decreasing in size right and leftward */

	{ "[D]",	deck },	                /* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },              /* All windows on top of eachother */

	{ "|M|",	centeredmaster },               /* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },       /* Same but master floats */

	{ "><>",	NULL },	                /* no layout function means floating behavior */
	{ NULL,		NULL },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char *termcmd[]  = { TERMINAL, NULL };

#define VOLUME(args)     SHCMD("wpctl " args "; pkill -RTMIN+12 dwmblocks")
#define BRIGHTNESS(step) SHCMD("brightnessctl -q set " step "; pkill -RTMIN+20 dwmblocks")

ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
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
#include "shiftview.c"

static const Key keys[] = {
	/* { MODKEY|ShiftMask,		XK_Escape,     spawn,	               SHCMD("") }, */
	{ MODKEY,			XK_grave,      spawn,	               {.v = (const char*[]){ "dmenuunicode", NULL } } },
	/* { MODKEY|ShiftMask,		XK_grave,      togglescratch,	       SHCMD("") }, */
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
	/* { MODKEY|ShiftMask,		XK_Tab,	       spawn,                  SHCMD("") }, */
	{ MODKEY,			XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,		XK_q,          spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY,			XK_w,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,		XK_w,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "nmtui", NULL } } },
	{ MODKEY,			XK_e,          spawn,                  SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_e,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "abook", NULL } } },
	{ MODKEY,			XK_r,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
	{ MODKEY|ShiftMask,		XK_r,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEY,			XK_t,          setlayout,              {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,          setlayout,              {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,          setlayout,              {.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,          setlayout,              {.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,          setlayout,              {.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,          setlayout,              {.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,          setlayout,              {.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,          setlayout,              {.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,			XK_o,          incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,          incnmaster,             {.i = -1 } },
	{ MODKEY,			XK_p,          spawn,                  {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ MODKEY|ShiftMask,		XK_p,          spawn,                  SHCMD("mpc pause; pauseallmpv") },
	{ MODKEY,			XK_bracketleft, spawn,                 {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ MODKEY|ShiftMask,		XK_bracketleft, spawn,                 {.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
	{ MODKEY,			XK_bracketright, spawn,                {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ MODKEY|ShiftMask,		XK_bracketright, spawn,                {.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
	{ MODKEY,			XK_backslash,  view,                   {0} },
	/* { MODKEY|ShiftMask,		XK_backslash,  spawn,                  SHCMD("") }, */

	{ MODKEY,			XK_a,          togglegaps,             {0} },
	{ MODKEY|ShiftMask,		XK_a,          defaultgaps,            {0} },
	{ MODKEY,			XK_s,          togglesticky,           {0} },
	/* { MODKEY|ShiftMask,		XK_s,          spawn,                  SHCMD("") }, */
	{ MODKEY,			XK_d,          spawn,                  {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY|ShiftMask,		XK_d,          spawn,                  {.v = (const char*[]){ "passmenu", NULL } } },
	{ MODKEY,			XK_f,          togglefullscr,          {0} },
	{ MODKEY|ShiftMask,		XK_f,          setlayout,              {.v = &layouts[8]} },
	{ MODKEY,			XK_g,          shiftview,              { .i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,          shifttag,               { .i = -1 } },
	{ MODKEY,			XK_h,          setmfact,               {.f = -0.05} },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,			XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,			XK_semicolon,  shiftview,              { .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,  shifttag,               { .i = 1 } },
	{ MODKEY,			XK_apostrophe, togglescratch,          {.ui = 1} },
	/* { MODKEY|ShiftMask,		XK_apostrophe, spawn,                  SHCMD("") }, */
	{ MODKEY|ShiftMask,		XK_apostrophe, togglesmartgaps,        {0} },
	{ MODKEY,			XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,     togglescratch,          {.ui = 0} },

	{ MODKEY,			XK_z,          incrgaps,               {.i = +3 } },
	/* { MODKEY|ShiftMask,		XK_z,          spawn,                  SHCMD("") }, */
	{ MODKEY,			XK_x,          incrgaps,               {.i = -3 } },
	/* { MODKEY|ShiftMask,		XK_x,          spawn,                  SHCMD("") }, */
	{ MODKEY,			XK_c,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "profanity", NULL } } },
	/* { MODKEY|ShiftMask,		XK_c,          spawn,                  SHCMD("") }, */
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,			XK_b,          togglebar,              {0} },
	/* { MODKEY|ShiftMask,		XK_b,          spawn,                  SHCMD("") }, */
	{ MODKEY,			XK_n,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "nvim", "-c", "VimwikiIndex", NULL } } },
	{ MODKEY|ShiftMask,		XK_n,          spawn,                  SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY,			XK_m,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ MODKEY|ShiftMask,		XK_m,          spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ MODKEY|ShiftMask,		XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
	{ MODKEY,			XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ MODKEY|ShiftMask,		XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "repeat", NULL } } },

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

	{ MODKEY,			XK_F1,         spawn,                  SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
	{ MODKEY,			XK_F2,         spawn,                  {.v = (const char*[]){ "tutorialvids", NULL } } },
	{ MODKEY,			XK_F3,         spawn,                  {.v = (const char*[]){ "displayselect", NULL } } },
	{ MODKEY,			XK_F4,         spawn,                  SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_F5,         xrdb,                   {.v = NULL } },
	{ MODKEY,			XK_F6,         spawn,                  {.v = (const char*[]){ "torwrap", NULL } } },
	{ MODKEY,			XK_F7,         spawn,                  {.v = (const char*[]){ "td-toggle", NULL } } },
	{ MODKEY,			XK_F8,         spawn,                  {.v = (const char*[]){ "mailsync", NULL } } },
	{ MODKEY,			XK_F9,         spawn,                  {.v = (const char*[]){ "mounter", NULL } } },
	{ MODKEY,			XK_F10,        spawn,                  {.v = (const char*[]){ "unmounter", NULL } } },
	{ MODKEY,			XK_F11,        spawn,                  SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_F12,        spawn,                  SHCMD("remaps") },
	{ MODKEY,			XK_space,      zoom,                   {0} },
	{ MODKEY|ShiftMask,		XK_space,      togglefloating,         {0} },

	{ 0,				XK_Print,      spawn,                  SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,      spawn,                  {.v = (const char*[]){ "maimpick", NULL } } },
	{ MODKEY,			XK_Print,      spawn,		       {.v = (const char*[]){ "dmenurecord", NULL } } },
	{ MODKEY|ShiftMask,		XK_Print,      spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	{ MODKEY,			XK_Delete,     spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	{ MODKEY,			XK_Scroll_Lock, spawn,                 SHCMD("killall screenkey || screenkey &") },

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

	/* { MODKEY|Mod4Mask,           XK_h,          incrgaps,               {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,           XK_l,          incrgaps,               {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask, XK_h,          incrogaps,              {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask, XK_l,          incrogaps,              {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask, XK_h,        incrigaps,              {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask, XK_l,        incrigaps,              {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask, XK_0,          defaultgaps,            {0} }, */
	/* { MODKEY,                    XK_y,          incrihgaps,             {.i = +1 } }, */
	/* { MODKEY,                    XK_o,          incrihgaps,             {.i = -1 } }, */
	/* { MODKEY|ControlMask,        XK_y,          incrivgaps,             {.i = +1 } }, */
	/* { MODKEY|ControlMask,        XK_o,          incrivgaps,             {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,           XK_y,          incrohgaps,             {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,           XK_o,          incrohgaps,             {.i = -1 } }, */
	/* { MODKEY|ShiftMask,          XK_y,          incrovgaps,             {.i = +1 } }, */
	/* { MODKEY|ShiftMask,          XK_o,          incrovgaps,             {.i = -1 } }, */

};

static const Button buttons[] = {
	/* click                event mask           button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,                   Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,                   Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,                   Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,                   Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,           Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,           Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        defaultgaps,    {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		     Button4,	     incrgaps,       {.i = +1} },
	{ ClkClientWin,		MODKEY,		     Button5,	     incrgaps,       {.i = -1} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		     Button4,	     shiftview,      {.i = -1} },
	{ ClkTagBar,		0,		     Button5,	     shiftview,      {.i = 1} },
	{ ClkRootWin,		0,		     Button2,	     togglebar,      {0} },
};
