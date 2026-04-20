static const Block blocks[] = {
	/* icon  command         interval  signal */
	{ "",    "sb-music",     2,        6 },
	{ "",    "sb-network",   10,       4 },
	{ "",    "sb-bluetooth", 10,       5 },
	{ "",    "sb-volume",    0,        3 },
	{ "",    "sb-battery",   30,       2 },
	{ "",    "sb-clock",     30,       1 },
};

static char delim[] = " | ";
static unsigned int delimLen = 3;
