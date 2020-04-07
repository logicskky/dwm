/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 10;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 10;  /* vert outer gap between windows and screen edge */
static const int smartgaps               = 1;   /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 0;   /* 0 means bottom bar */
static const char *fonts[]               = { "Source Code Pro:size=12" };
static const char dmenufont[]            = "Source Code Pro:size=12";
static const char dmenuborderwidth[]     = "2";
static const char dmenulist[]            = "15";
static const char dmenucolor[]           = "#2D4D7D";
static const char col_gray1[]            = "#222222";
static const char col_gray2[]            = "#444444";
static const char col_gray3[]            = "#bbbbbb";
static const char col_gray4[]            = "#ffffff";
static const char col_cyan[]             = "#37474F";
static const char col_border[]           = "#42A5F5";
static const unsigned int baralpha       = 0xd0;
static const unsigned int borderalpha    = OPAQUE;
static const char *colors[][3]           = {
	/*               fg         bg         border      */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2   },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_border  },
};
static const unsigned int alphas[][3]    = {
	/*               fg      bg        border      */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
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
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact      = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const int resizehints  = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol    arrange function */
	{ "Tile",    tile             },    /* first entry is default */
	{ "Float",   NULL             },    /* no layout function means floating behavior */
	{ "Monocle", monocle          },
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
static char        dmenumon[2]   = "0";   /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", dmenucolor, "-sf", col_gray4, "-l", dmenulist, "-i", "-bw", dmenuborderwidth, NULL };
static const char *termcmd[]     = { "st", NULL };
static const char *browsercmd[]  = { "google-chrome-stable", NULL };

static const char *upvol[]   = { "~/Program/dwm/scripts/vol-up.sh",      NULL };
static const char *downvol[] = { "~/Program/dwm/scripts/vol-down.sh",    NULL };
static const char *mutevol[] = { "~/Program/dwm/scripts/vol-toggle.sh",  NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "60x20", NULL };

static Key keys[] = {
	/* modifier                     key            function        argument              */
	{ MODKEY,                       XK_d,          spawn,          {.v = dmenucmd }      },
	{ MODKEY,                       XK_Return,     spawn,          {.v = termcmd }       },
	{ MODKEY,                       XK_c,          spawn,          {.v = browsercmd }    },
	{ MODKEY|ControlMask,           XK_i,          spawn,          {.v = upvol }         },
	{ MODKEY|ControlMask,           XK_k,          spawn,          {.v = downvol }       },
	{ MODKEY|ControlMask,           XK_m,          spawn,          {.v = mutevol }       },
	{ MODKEY,                       XK_apostrophe, togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,          togglebar,      {0}                   },
	{ MODKEY|ShiftMask,             XK_k,          rotatestack,    {.i = +1 }            },
	{ MODKEY|ShiftMask,             XK_i,          rotatestack,    {.i = -1 }            },
	{ MODKEY,                       XK_k,          focusstack,     {.i = +1 }            },
	{ MODKEY,                       XK_i,          focusstack,     {.i = -1 }            },
	{ MODKEY,                       XK_h,          incnmaster,     {.i = +1 }            },
	{ MODKEY,                       XK_p,          incnmaster,     {.i = -1 }            },
	{ MODKEY,                       XK_j,          setmfact,       {.f = -0.05}          },
	{ MODKEY,                       XK_l,          setmfact,       {.f = +0.05}          },
	{ MODKEY|Mod1Mask,              XK_j,          incrgaps,       {.i = +1 }            },
	{ MODKEY|Mod1Mask,              XK_l,          incrgaps,       {.i = -1 }            },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_j,          incrogaps,      {.i = +1 }            },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,          incrogaps,      {.i = -1 }            },
	{ MODKEY|Mod1Mask|ControlMask,  XK_j,          incrigaps,      {.i = +1 }            },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,          incrigaps,      {.i = -1 }            },
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,     {0}                   },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,    {0}                   },
	{ MODKEY,                       XK_u,          incrihgaps,     {.i = +1 }            },
	{ MODKEY,                       XK_o,          incrihgaps,     {.i = -1 }            },
	{ MODKEY|ControlMask,           XK_u,          incrivgaps,     {.i = +1 }            },
	{ MODKEY|ControlMask,           XK_o,          incrivgaps,     {.i = -1 }            },
	{ MODKEY|Mod1Mask,              XK_u,          incrohgaps,     {.i = +1 }            },
	{ MODKEY|Mod1Mask,              XK_o,          incrohgaps,     {.i = -1 }            },
	{ MODKEY|ShiftMask,             XK_u,          incrovgaps,     {.i = +1 }            },
	{ MODKEY|ShiftMask,             XK_o,          incrovgaps,     {.i = -1 }            },
	{ MODKEY|ShiftMask,             XK_Return,     zoom,           {0}                   },
	{ MODKEY,                       XK_Tab,        view,           {0}                   },
	{ MODKEY|ControlMask,           XK_q,          killclient,     {0}                   },
	{ MODKEY|ShiftMask,             XK_t,          setlayout,      {.v = &layouts[0]}    },
	{ MODKEY|ShiftMask,             XK_f,          setlayout,      {.v = &layouts[1]}    },
	{ MODKEY|ShiftMask,             XK_m,          setlayout,      {.v = &layouts[2]}    },
	{ MODKEY,                       XK_f,          fullscreen,     {0}                   },
	{ MODKEY,                       XK_space,      setlayout,      {0}                   },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating, {0}                   },
	{ MODKEY,                       XK_0,          view,           {.ui = ~0 }           },
	{ MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 }           },
	{ MODKEY,                       XK_comma,      focusmon,       {.i = -1 }            },
	{ MODKEY,                       XK_period,     focusmon,       {.i = +1 }            },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 }            },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 }            },
	TAGKEYS(                        XK_1,          0                                     )
	TAGKEYS(                        XK_2,          1                                     )
	TAGKEYS(                        XK_3,          2                                     )
	TAGKEYS(                        XK_4,          3                                     )
	TAGKEYS(                        XK_5,          4                                     )
	TAGKEYS(                        XK_6,          5                                     )
	TAGKEYS(                        XK_7,          6                                     )
	TAGKEYS(                        XK_8,          7                                     )
	TAGKEYS(                        XK_9,          8                                     )
	{ MODKEY|ControlMask|ShiftMask, XK_c,          quit,           {0}                   },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument           */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0}                },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0}                },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0}                },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd }    },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0}                },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0}                },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0}                },
	{ ClkTagBar,            0,              Button1,        view,           {0}                },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0}                },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0}                },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0}                },
};

