/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nobody";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#1f2430",   /* after initialization */
	[INPUT] =  "#666666",   /* during input (gray) */
	[FAILED] = "#f28779",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
