#!/bin/sh
set -eu

cd "$(dirname "$0")"

doas_cmd="doas"

PACMAN_PKGS="
xorg-server xorg-xinit xorg-xrdb xorg-xsetroot xorg-xrandr xorg-setxkbmap xorg-xinput
base-devel libx11 libxi libxinerama libxft libxext libxrandr libxrender fontconfig freetype2
git unzip curl fzf fastfetch
dunst picom mpd mpc ncmpcpp mpv yt-dlp mpv-mpris playerctl
pipewire pipewire-pulse wireplumber pulsemixer
networkmanager bluez bluez-utils brightnessctl gammastep xwallpaper
maim slop xclip xdotool wmctrl libnotify ffmpeg lsof gawk python vim
xdg-desktop-portal xdg-desktop-portal-gtk
"

# from the aur (yay): ytfzf, bluetui (bt-console), xkblayout-state (kb-layout)
AUR_PKGS="xkblayout-state-git ytfzf bluetui"

install_deps() {
	$doas_cmd pacman -S --needed --noconfirm $PACMAN_PKGS
	if command -v yay >/dev/null 2>&1; then
		yay -S --needed --noconfirm $AUR_PKGS || true
	else
		echo "yay not found - skipping aur packages: $AUR_PKGS" >&2
	fi
}

# dwm/dmenu/st -> ~/.local/bin; slock setuid-root -> /usr/local/bin
build_suckless() {
	for dir in dwm dmenu st; do
		make -C "$dir" clean
		make -C "$dir" PREFIX="$HOME/.local" install
	done
	make -C slock clean
	$doas_cmd make -C slock install
}

install_deps
build_suckless
