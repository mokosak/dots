#!/bin/sh
set -eu

cd "$(dirname "$0")"


# dwm/dmenu/st -> ~/.local/bin
build_suckless() {
	for dir in dwm dmenu st; do
		make -C "$dir" clean
		make -C "$dir" PREFIX="$HOME/.local" install
	done
}

build_suckless
