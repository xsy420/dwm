#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=15" };
static const char dmenufont[]       = "monospace:size=18";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
//#define MODKEY Mod1Mask //MODKEY = Alt
#define MODKEY Mod4Mask //MODKEY = Windows
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *slockcmd[] = { "slock", NULL };
static const char *roficmd[] = { "rofi", "-show", "combi", "-combi-modes" , "window,drun,run,ssh", "-modes", "combi", NULL};
static const char *flameshotcmd[] = { "flameshot", "gui", NULL };
static const char *rangercmd[] = { "st", "-e", "ranger", NULL };
static const char *edgecmd[] = { "microsoft-edge-dev", "--inprivate", NULL };
static const char *ideacmd[] = { "idea", NULL };
static const char *webstormcmd[] = { "webstorm", NULL };
static const char *pycharmcmd[] = { "pycharm", NULL };
static const char *btopcmd[] = { "st", "-e", "btop", NULL };
static const char *navicatcmd[] = { "Navicat", NULL };
static const char *feishucmd[] = { "feishu", NULL };
static const char *vlccmd[] = { "vlc", NULL };
static const char *rebootcmd[] = { "reboot", NULL };
static const char *codecmd[] = { "code", NULL };
static const char *volupcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "5%+", NULL };
static const char *voldowncmd[] = { "amixer", "-D", "pulse", "sset", "Master", "5%-", NULL };
static const char *volmutecmd[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *brightupcmd[] = { "sudo", "light", "-A", "5", NULL };
static const char *brightdowncmd[] = { "sudo", "light", "-U", "5", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	//{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_l,      spawn,          {.v = slockcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = flameshotcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = rangercmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = edgecmd } },
	{ MODKEY|ShiftMask,             XK_i,      spawn,          {.v = ideacmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = webstormcmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = pycharmcmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = btopcmd } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = navicatcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = feishucmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vlccmd } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = rebootcmd } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = codecmd } },
  { 0,              XF86XK_AudioLowerVolume, spawn,          {.v = voldowncmd } },
	{ 0,              XF86XK_AudioMute,        spawn,          {.v = volmutecmd } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = volupcmd   } },
	{ 0,              XF86XK_MonBrightnessUp,  spawn,          {.v = brightupcmd   } },
	{ 0,              XF86XK_MonBrightnessDown,spawn,          {.v = brightdowncmd   } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ Mod1Mask,                     XK_j,      focusstack,     {.i = +1 } },
	{ Mod1Mask,                     XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ Mod1Mask,                     XK_h,      setmfact,       {.f = -0.05} },
	{ Mod1Mask,                     XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,                     XK_space,  killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ ControlMask,                  XK_Return, fullscreen,     {0} },
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

