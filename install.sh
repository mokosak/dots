#!/bin/sh

set -eu

cd "$(dirname "$0")"

if command -v doas >/dev/null 2>&1; then root=doas; else root=sudo; fi

DEBIAN_PKGS="
build-essential pkg-config libx11-dev libxft-dev libxinerama-dev libx11-xcb-dev
libxcb-res0-dev libharfbuzz-dev libfreetype-dev libfontconfig-dev
x11-xserver-utils xinit fonts-noto-color-emoji fonts-font-awesome bluez
picom dunst libnotify-bin
pipewire-pulse wireplumber pulsemixer
mpd mpc ncmpcpp newsboat
maim xclip xdotool xwallpaper brightnessctl
lm-sensors htop psmisc suckless-tools network-manager xdg-utils file firefox-esr
thunar gvfs xdg-desktop-portal-gtk gnome-keyring libpam-gnome-keyring lxpolkit
xss-lock zathura zathura-pdf-poppler nsxiv qt5ct
curl unzip
"

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
	if command -v apt-get >/dev/null 2>&1; then
		$root apt-get update
		$root apt-get install -y $DEBIAN_PKGS
		$root systemctl disable --now mpd.service mpd.socket >/dev/null 2>&1 || :
	elif command -v pacman >/dev/null 2>&1; then
		$root pacman -S --needed --noconfirm $ARCH_PKGS
	else
		echo "no apt or pacman: install the packages listed in install.sh yourself" >&2
		exit 1
	fi
}

install_iosevka() {
	fc-list "Iosevka Term" family | grep -q . && return 0
	tmp=$(mktemp -d)
	url=$(curl -fsSL https://api.github.com/repos/be5invis/Iosevka/releases/latest |
		grep -o '"browser_download_url": *"[^"]*/PkgTTC-Iosevka-[0-9.]*\.zip"' | cut -d'"' -f4)
	curl -fL --proto '=https' --tlsv1.2 -o "$tmp/iosevka.zip" "$url"
	mkdir -p "$HOME/.local/share/fonts/iosevka"
	unzip -o -j "$tmp/iosevka.zip" 'Iosevka-Regular.ttc' 'Iosevka-Light.ttc' 'Iosevka-Bold.ttc' \
		-d "$HOME/.local/share/fonts/iosevka" >/dev/null
	rm -rf "$tmp"
	fc-cache -f "$HOME/.local/share/fonts"
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
	copy config/ncmpcpp/bindings   "$cfg/ncmpcpp/bindings"
	copy config/newsboat/config    "$cfg/newsboat/config"
	copy config/fontconfig/60-iosevka-color-emoji.conf "$cfg/fontconfig/conf.d/60-iosevka-color-emoji.conf"
	copy config/gtk-3.0/settings.ini "$cfg/gtk-3.0/settings.ini"
	copy config/gtk-4.0/settings.ini "$cfg/gtk-4.0/settings.ini"
	copy config/xdg-desktop-portal/dwm-portals.conf "$cfg/xdg-desktop-portal/dwm-portals.conf"
	command -v firefox-esr >/dev/null 2>&1 && copy config/dmenu/hidden "$cfg/dmenu/hidden"
	copy config/zathura/zathurarc  "$cfg/zathura/zathurarc"
	copy config/bluetuith/bluetuith.conf "$cfg/bluetuith/bluetuith.conf"
	copy config/systemd/user/mpd.socket.d/localhost.conf "$cfg/systemd/user/mpd.socket.d/localhost.conf"
	systemctl --user daemon-reload 2>/dev/null && systemctl --user enable mpd.socket 2>/dev/null || :
	copy config/qt5ct/colors/gruvbox.conf "$cfg/qt5ct/colors/gruvbox.conf"
	sed "s|@HOME@|$HOME|" config/qt5ct/qt5ct.conf > "${TMPDIR:-/tmp}/qt5ct.conf"
	copy "${TMPDIR:-/tmp}/qt5ct.conf" "$cfg/qt5ct/qt5ct.conf"
	mkdir -p "$cfg/mpd/playlists" "$HOME/Music" "$HOME/Pictures/Screenshots"
}

BLUETUITH_VERSION=0.2.7
BLUETUITH_SHA256=145888f0e3959d29832c7395403c2327e0f03b9591e4cdd3f712741cf0f934e9
install_bluetuith() {
	[ -x "$HOME/.local/bin/bluetuith" ] && return 0
	[ "$(uname -m)" = x86_64 ] || return 0
	tmp=$(mktemp -d)
	curl -fL --proto '=https' --tlsv1.2 -o "$tmp/bluetuith.tar.gz" \
		"https://github.com/bluetuith-org/bluetuith/releases/download/v$BLUETUITH_VERSION/bluetuith_${BLUETUITH_VERSION}_Linux_x86_64.tar.gz"
	echo "$BLUETUITH_SHA256  $tmp/bluetuith.tar.gz" | sha256sum -c - >/dev/null || {
		echo "bluetuith download doesn't match the reviewed version, skipping" >&2
		rm -rf "$tmp"; return 0; }
	tar xzf "$tmp/bluetuith.tar.gz" -C "$tmp" bluetuith
	install -Dm755 "$tmp/bluetuith" "$HOME/.local/bin/bluetuith"
	rm -rf "$tmp"
}

set_default_apps() {
	apps=/usr/share/applications
	[ -e "$apps/org.pwmt.zathura-pdf-poppler.desktop" ] &&
		xdg-mime default org.pwmt.zathura-pdf-poppler.desktop application/pdf
	[ -e "$apps/nsxiv.desktop" ] &&
		xdg-mime default nsxiv.desktop image/png image/jpeg image/gif image/webp image/bmp image/tiff
	return 0
}

session_note="log in on tty1 and run startx."
install_deps
install_iosevka
build_suckless
install_scripts
install_configs
install_bluetuith
set_default_apps

echo "done. $session_note"
