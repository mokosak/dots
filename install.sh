#!/bin/sh

set -eu

cd "$(dirname "$0")"

if command -v doas >/dev/null 2>&1; then root=doas; else root=sudo; fi

ARCH_PKGS="
xorg-server xorg-xinit xorg-xrdb xorg-xsetroot xorg-xset
base-devel libx11 libxft libxinerama libxcb harfbuzz fontconfig freetype2
ttc-iosevka noto-fonts-emoji ttf-font-awesome bluez bluez-utils
picom dunst libnotify
pipewire pipewire-pulse wireplumber pulsemixer
mpd mpc ncmpcpp newsboat
maim xclip xdotool xwallpaper brightnessctl
lm_sensors htop psmisc slock networkmanager xdg-utils file firefox
thunar gvfs xdg-desktop-portal-gtk gnome-keyring
xss-lock zathura zathura-pdf-poppler nsxiv qt5ct
"

install_deps() {
	$root pacman -S --needed --noconfirm $ARCH_PKGS
}

build_suckless() {
	src="$HOME/.local/src/dots"
	if [ "$(pwd -P)" != "$(cd "$src" 2>/dev/null && pwd -P)" ]; then
		mkdir -p "$src"
		cp -R . "$src/"
	fi
	for dir in dwm dmenu st dwmblocks; do
		make -C "$src/$dir" PREFIX="$HOME/.local" install
		make -C "$src/$dir" clean
	done
}

install_scripts() {
	for script in bin/*; do
		install -Dm755 "$script" "$HOME/.local/bin/${script#bin/}"
	done
}

copy() {
	if [ -e "$2" ] && [ ! -e "$2.bak-larbs" ]; then
		cp -a "$2" "$2.bak-larbs"
	fi
	install -Dm"${3:-644}" "$1" "$2"
}

install_configs() {
	cfg="${XDG_CONFIG_HOME:-$HOME/.config}"
	copy config/x11/xinitrc        "$HOME/.xinitrc" 755
	copy config/x11/xresources     "$cfg/x11/xresources"
	copy config/dunst/dunstrc      "$cfg/dunst/dunstrc"
	copy config/picom/picom.conf   "$cfg/picom/picom.conf"
	copy config/mpd/mpd.conf       "$cfg/mpd/mpd.conf"
	copy config/ncmpcpp/config     "$cfg/ncmpcpp/config"
	copy config/gtk-3.0/settings.ini "$cfg/gtk-3.0/settings.ini"
	copy config/gtk-4.0/settings.ini "$cfg/gtk-4.0/settings.ini"
	mkdir -p "$cfg/mpd/playlists" "$HOME/Music" "$HOME/Pictures/Screenshots"
}

session_note="log in on tty1 and run startx."
install_deps
build_suckless
install_scripts
install_configs

echo "done. $session_note"
