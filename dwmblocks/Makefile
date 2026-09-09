.POSIX:

PREFIX = /usr/local
CC = gcc

all: dwmblocks xkblayout
dwmblocks: dwmblocks.o
	$(CC) dwmblocks.o -lX11 -o dwmblocks
dwmblocks.o: dwmblocks.c config.h
	$(CC) -c dwmblocks.c
xkblayout: xkblayout.c
	$(CC) -O2 -Wall xkblayout.c -lX11 -o xkblayout
clean:
	rm -f *.o *.gch dwmblocks xkblayout
install: dwmblocks xkblayout
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f dwmblocks xkblayout $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dwmblocks $(DESTDIR)$(PREFIX)/bin/xkblayout
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dwmblocks $(DESTDIR)$(PREFIX)/bin/xkblayout

.PHONY: all clean install uninstall
