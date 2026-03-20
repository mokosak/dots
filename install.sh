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

install_font() {
	fc-match "SpaceMono Nerd Font" 2>/dev/null | grep -qi Space && return 0
	tmp=${TMPDIR:-/tmp}/SpaceMono.zip
	mkdir -p "$HOME/.local/share/fonts/SpaceMonoNerdFont"
	curl -fL --proto '=https' --tlsv1.2 -o "$tmp" \
		https://github.com/ryanoasis/nerd-fonts/releases/latest/download/SpaceMono.zip
	unzip -o "$tmp" -d "$HOME/.local/share/fonts/SpaceMonoNerdFont" >/dev/null
	fc-cache -f "$HOME/.local/share/fonts"
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

install_scripts() {
	mkdir -p "$HOME/.local/bin" "$HOME/.local/share/mpd/playlists"
	for script in scripts/*; do
		install -Dm755 "$script" "$HOME/.local/bin/$(basename "$script")"
	done
}

copy() { install -Dm"${3:-644}" "$1" "$2"; }

install_configs() {
	copy config/ncmpcpp/config              "$HOME/.config/ncmpcpp/config"
	copy config/mpd/mpd.conf                "$HOME/.config/mpd/mpd.conf"
}

install_deps
install_font
build_suckless
install_scripts
install_configs
