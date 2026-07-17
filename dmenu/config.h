static int topbar = 1;
static const char *fonts[] = {
	"Iosevka:size=12",
	"Noto Color Emoji:pixelsize=12:antialias=true:autohint=true"
};
static const unsigned int bgalpha = OPAQUE;
static const unsigned int fgalpha = OPAQUE;
static const char *prompt      = NULL;
static const char *colors[SchemeLast][2] = {
	[SchemeNorm] = { "#ebdbb2", "#1d2021" },
	[SchemeSel] = { "#1d2021", "#83a598" },
	[SchemeOut] = { "#000000", "#00ffff" },
};
static const unsigned int alphas[SchemeLast][2] = {
	[SchemeNorm] = { fgalpha, bgalpha },
	[SchemeSel] = { fgalpha, bgalpha },
	[SchemeOut] = { fgalpha, bgalpha },
};

static unsigned int lines      = 0;

static const char worddelimiters[] = " ";
