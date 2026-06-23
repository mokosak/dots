#!/bin/sh
# build dwm/dmenu/st/slock/dwmblocks, drop the scripts and configs in place.
# no display manager - log in on tty1 and startx fires from ~/.bash_profile.
# arch only. run from the repo root: ./install.sh
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

# spleen bitmap font: .bdf/.pcf for xft (dwm/dmenu/st), .otb for pango (dunst),
# and a 16x32 console face for the tty.
install_spleen() {
	ver=2.2.0
	tmp=${TMPDIR:-/tmp}/spleen-$ver
	if [ ! -d "$tmp" ]; then
		curl -fL --proto '=https' --tlsv1.2 -o "$tmp.tar.gz" \
			"https://github.com/fcambus/spleen/releases/download/$ver/spleen-$ver.tar.gz"
		tar xzf "$tmp.tar.gz" -C "${TMPDIR:-/tmp}"
	fi
	if ! fc-match "Spleen" 2>/dev/null | grep -qi spleen; then
		mkdir -p "$HOME/.local/share/fonts/spleen"
		cp "$tmp"/spleen-*.bdf "$tmp"/spleen-*.pcf "$HOME/.local/share/fonts/spleen/"
		fc-cache -f "$HOME/.local/share/fonts"
	fi
	if [ ! -d "$HOME/.local/share/fonts/spleen-otb" ]; then
		mkdir -p "$HOME/.local/share/fonts/spleen-otb"
		cp "$tmp"/spleen-*.otb "$HOME/.local/share/fonts/spleen-otb/"
		fc-cache -f "$HOME/.local/share/fonts"
	fi
	if [ ! -f /usr/share/kbd/consolefonts/spleen-16x32.psfu.gz ]; then
		gzip -kf "$tmp"/spleen-12x24.psfu "$tmp"/spleen-16x32.psfu
		$doas_cmd install -m644 "$tmp"/spleen-12x24.psfu.gz "$tmp"/spleen-16x32.psfu.gz /usr/share/kbd/consolefonts/
		$doas_cmd sed -i 's/^FONT=.*/FONT=spleen-16x32/' /etc/vconsole.conf
	fi
}

# ble.sh - bash line editor (autosuggestions + syntax highlighting)
install_blesh() {
	[ -r "$HOME/.local/share/blesh/ble.sh" ] && return 0
	tmp=$(mktemp -d)
	git clone --recursive --depth 1 --shallow-submodules https://github.com/akinomyoga/ble.sh.git "$tmp/ble.sh"
	make -C "$tmp/ble.sh" install PREFIX="$HOME/.local"
	rm -rf "$tmp"
}

# dwm/dmenu/st/dwmblocks -> ~/.local/bin; slock setuid-root -> /usr/local/bin
build_suckless() {
	for dir in dwm dmenu st dwmblocks; do
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
	for so in /usr/lib/mpv-mpris/mpris.so /usr/lib/*/mpv-mpris/mpris.so /etc/mpv/scripts/mpris.so; do
		[ -e "$so" ] && { mkdir -p "$HOME/.config/mpv/scripts"; ln -sfn "$so" "$HOME/.config/mpv/scripts/mpris.so"; break; }
	done
}

copy() { install -Dm"${3:-644}" "$1" "$2"; }

install_configs() {
	copy config/dunst/dunstrc               "$HOME/.config/dunst/dunstrc"
	copy config/ncmpcpp/config              "$HOME/.config/ncmpcpp/config"
	copy config/mpd/mpd.conf                "$HOME/.config/mpd/mpd.conf"
	copy config/slop/clearselect.frag       "$HOME/.config/slop/clearselect.frag"
	copy config/slop/clearselect.vert       "$HOME/.config/slop/clearselect.vert"
	copy config/picom/picom.conf            "$HOME/.config/picom/picom.conf"
	copy config/gtk-3.0/settings.ini        "$HOME/.config/gtk-3.0/settings.ini"
	copy config/gtk-4.0/settings.ini        "$HOME/.config/gtk-4.0/settings.ini"
	copy config/gtk-3.0/gtk.css             "$HOME/.config/gtk-3.0/gtk.css"
	copy config/gtk-4.0/gtk.css             "$HOME/.config/gtk-4.0/gtk.css"
	copy config/fontconfig/fonts.conf       "$HOME/.config/fontconfig/fonts.conf"
	copy config/icons/default/index.theme   "$HOME/.icons/default/index.theme"

	# $HOME dotfiles - back the originals up once
	for f in "$HOME/.gtkrc-2.0" "$HOME/.bashrc" "$HOME/.bash_profile" "$HOME/.xinitrc" "$HOME/.Xresources" "$HOME/.vimrc"; do
		[ -e "$f" ] && [ ! -e "$f.bak-suckless" ] && cp -a "$f" "$f.bak-suckless"
	done
	copy config/gtkrc-2.0         "$HOME/.gtkrc-2.0"
	copy config/bash/bashrc       "$HOME/.bashrc"
	copy config/bash/bash_profile "$HOME/.bash_profile"
	copy config/xinitrc           "$HOME/.xinitrc" 755
	copy config/Xresources   "$HOME/.Xresources"
	copy config/vim/vimrc    "$HOME/.vimrc"
}

# keyboard layout + boot to tty1, no greeter
install_system() {
	$doas_cmd mkdir -p /etc/X11/xorg.conf.d
	$doas_cmd cp config/X11/xorg.conf.d/00-keyboard.conf /etc/X11/xorg.conf.d/00-keyboard.conf
	$doas_cmd chsh -s /bin/bash "$(id -un)" >/dev/null 2>&1 || true
	$doas_cmd systemctl set-default multi-user.target >/dev/null
	$doas_cmd systemctl enable getty@tty1.service >/dev/null 2>&1 || true
}

install_deps
install_font
install_spleen
install_blesh
build_suckless
install_scripts
install_configs
install_system

echo "done. log out (or reboot) - tty1 starts x. lock with mod+x."
