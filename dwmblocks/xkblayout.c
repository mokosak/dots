#include <stdio.h>
#include <string.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

static void
printlayout(Display *dpy, int n)
{
	Atom type;
	int format, i;
	unsigned long len, extra;
	unsigned char *data = NULL;
	char *field, *tok = NULL;

	if (XGetWindowProperty(dpy, DefaultRootWindow(dpy),
	    XInternAtom(dpy, "_XKB_RULES_NAMES", False), 0, 1024, False, XA_STRING,
	    &type, &format, &len, &extra, &data) == Success && data) {
		field = (char *)data;
		for (i = 0; i < 2 && field < (char *)data + len; i++)
			field += strlen(field) + 1;
		if (field < (char *)data + len)
			for (tok = strtok(field, ","), i = 0; tok && i < n; i++)
				tok = strtok(NULL, ",");
	}
	if (tok)
		printf("%s\n", tok);
	else
		printf("%d\n", n + 1);
	fflush(stdout);
	if (data)
		XFree(data);
}

static int
group(Display *dpy)
{
	XkbStateRec state;

	XkbGetState(dpy, XkbUseCoreKbd, &state);
	return state.group;
}

int
main(int argc, char *argv[])
{
	Display *dpy;
	XkbDescPtr kb;
	XEvent ev;
	int xkbevent, major = XkbMajorVersion, minor = XkbMinorVersion;

	if (!(dpy = XOpenDisplay(NULL))) {
		fputs("xkblayout: cannot open display\n", stderr);
		return 1;
	}
	if (!XkbQueryExtension(dpy, NULL, &xkbevent, NULL, &major, &minor)) {
		fputs("xkblayout: no XKB\n", stderr);
		return 1;
	}

	if (argc > 1 && !strcmp(argv[1], "next")) {
		if (!(kb = XkbAllocKeyboard()))
			return 1;
		XkbGetControls(dpy, XkbAllControlsMask, kb);
		if (kb->ctrls && kb->ctrls->num_groups > 1)
			XkbLockGroup(dpy, XkbUseCoreKbd, (group(dpy) + 1) % kb->ctrls->num_groups);
		XkbFreeKeyboard(kb, 0, True);
		XSync(dpy, False);
	} else if (argc > 1 && !strcmp(argv[1], "-w")) {
		XkbSelectEventDetails(dpy, XkbUseCoreKbd, XkbStateNotify,
			XkbGroupStateMask, XkbGroupStateMask);
		printlayout(dpy, group(dpy));
		for (;;) {
			XNextEvent(dpy, &ev);
			if (ev.type == xkbevent && ((XkbEvent *)&ev)->any.xkb_type == XkbStateNotify)
				printlayout(dpy, ((XkbEvent *)&ev)->state.group);
		}
	} else if (argc > 1) {
		fputs("usage: xkblayout [next | -w]\n", stderr);
		return 1;
	} else {
		printlayout(dpy, group(dpy));
	}
	XCloseDisplay(dpy);
	return 0;
}
