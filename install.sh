#!/bin/sh
set -eu

cd "$(dirname "$0")"

askpass=${SUDO_ASKPASS:-"$HOME/.local/bin/dmenupass"}
sudo_cmd="sudo"
[ -n "${DISPLAY:-}" ] && [ -x "$askpass" ] && sudo_cmd="sudo -A"

install_deps() {
	if command -v pacman >/dev/null 2>&1; then
		$sudo_cmd pacman -S --needed --noconfirm \
			xorg-server xorg-xinit xorg-xrdb xorg-xsetroot xorg-xrandr \
			base-devel libx11 libxi libxinerama libxft libxext libxrandr libxrender fontconfig freetype2 \
			git kitty zsh zsh-autosuggestions zsh-syntax-highlighting fzf yazi fastfetch greetd greetd-tuigreet \
			dunst picom mpd mpc ncmpcpp mpv yt-dlp ytfzf mpv-mpris jq playerctl pipewire pipewire-pulse wireplumber smartmontools \
			networkmanager bluez bluez-utils brightnessctl unzip curl xdg-desktop-portal xdg-desktop-portal-gtk \
			xwallpaper maim slop xclip xdotool xorg-xwininfo xorg-xev libnotify pulsemixer bluetui gammastep
		if command -v yay >/dev/null 2>&1; then
			yay -S --needed --noconfirm xdg-desktop-portal-termfilechooser xkblayout-state-git || true
		fi
	elif command -v apt-get >/dev/null 2>&1; then
		$sudo_cmd apt-get update
		$sudo_cmd apt-get install -y \
			xserver-xorg-core xinit x11-xserver-utils \
			build-essential libx11-dev libxi-dev libxinerama-dev libxft-dev libxext-dev libxrandr-dev libxrender-dev \
			libfontconfig-dev libfreetype6-dev git kitty zsh fzf \
			dunst picom mpd mpc ncmpcpp mpv yt-dlp jq playerctl smartmontools \
			pipewire pipewire-pulse wireplumber network-manager bluez brightnessctl unzip curl \
			xdg-desktop-portal xdg-desktop-portal-gtk \
			xwallpaper maim xclip xdotool x11-utils x11-apps libnotify-bin gammastep pulsemixer
		for pkg in fastfetch yazi slop greetd greetd-tuigreet zsh-autosuggestions zsh-syntax-highlighting mpv-mpris; do
			apt-cache show "$pkg" >/dev/null 2>&1 && $sudo_cmd apt-get install -y "$pkg" || true
		done
	fi
}

install_font() {
	if fc-match "SpaceMono Nerd Font" 2>/dev/null | grep -qi "Space"; then
		return
	fi
	tmp=${TMPDIR:-/tmp}/SpaceMono.zip
	mkdir -p "$HOME/.local/share/fonts/SpaceMonoNerdFont"
	curl -L -o "$tmp" https://github.com/ryanoasis/nerd-fonts/releases/latest/download/SpaceMono.zip
	unzip -o "$tmp" -d "$HOME/.local/share/fonts/SpaceMonoNerdFont" >/dev/null
	fc-cache -f "$HOME/.local/share/fonts"
}

install_oh_my_zsh() {
	if [ -d "$HOME/.oh-my-zsh" ]; then
		return
	fi
	command -v git >/dev/null 2>&1 || return
	git clone --depth=1 https://github.com/ohmyzsh/ohmyzsh.git "$HOME/.oh-my-zsh"
}

install_xkblayout_state() {
	command -v xkblayout-state >/dev/null 2>&1 && return
	command -v apt-get >/dev/null 2>&1 || return
	tmp=$(mktemp -d)
	git clone --depth=1 https://github.com/nonpop/xkblayout-state "$tmp/src" 2>/dev/null \
		|| { rm -rf "$tmp"; return; }
	make -C "$tmp/src" 2>/dev/null \
		&& install -Dm755 "$tmp/src/xkblayout-state" "$HOME/.local/bin/xkblayout-state"
	rm -rf "$tmp"
}

install_ytfzf() {
	command -v ytfzf >/dev/null 2>&1 && return
	command -v apt-get >/dev/null 2>&1 || return
	command -v git >/dev/null 2>&1 || return
	tmp=$(mktemp -d)
	git clone --depth=1 https://github.com/pystardust/ytfzf "$tmp/src" 2>/dev/null \
		|| { rm -rf "$tmp"; return; }
	make -C "$tmp/src" install PREFIX="$HOME/.local" 2>/dev/null || true
	rm -rf "$tmp"
}

backup() {
	[ -e "$1" ] || [ -L "$1" ] || return 0
	[ -e "$1.bak-suckless" ] || cp -a "$1" "$1.bak-suckless"
}

install_deps
install_font
install_oh_my_zsh
install_xkblayout_state
install_ytfzf

for dir in dwm dmenu slock dwmblocks; do
	make -C "$dir"
	$sudo_cmd make -C "$dir" install
done
install -Dm755 dwm/dwm "$HOME/.local/bin/dwm"

mkdir -p "$HOME/.local/bin" "$HOME/.config" "$HOME/.local/share/mpd/playlists"
for script in scripts/*; do
	install -Dm755 "$script" "$HOME/.local/bin/$(basename "$script")"
done

# Load mpv-mpris so mpv (yt playback) shows up in the bar and on media keys.
for so in /usr/lib/mpv-mpris/mpris.so /usr/lib/*/mpv-mpris/mpris.so /etc/mpv/scripts/mpris.so; do
	[ -e "$so" ] && { mkdir -p "$HOME/.config/mpv/scripts"; ln -sfn "$so" "$HOME/.config/mpv/scripts/mpris.so"; break; }
done

install -Dm644 config/kitty/kitty.conf "$HOME/.config/kitty/kitty.conf"
install -Dm644 config/dunst/dunstrc "$HOME/.config/dunst/dunstrc"
install -Dm644 config/ncmpcpp/config "$HOME/.config/ncmpcpp/config"
install -Dm644 config/mpd/mpd.conf "$HOME/.config/mpd/mpd.conf"
install -Dm644 config/fastfetch/config.jsonc "$HOME/.config/fastfetch/config.jsonc"
install -Dm644 config/fastfetch/cow.txt "$HOME/.config/fastfetch/cow.txt"
install -Dm644 config/slop/clearselect.frag "$HOME/.config/slop/clearselect.frag"
install -Dm644 config/slop/clearselect.vert "$HOME/.config/slop/clearselect.vert"
install -Dm644 config/picom/picom.conf "$HOME/.config/picom/picom.conf"
install -Dm644 config/gtk-3.0/settings.ini "$HOME/.config/gtk-3.0/settings.ini"
install -Dm644 config/gtk-4.0/settings.ini "$HOME/.config/gtk-4.0/settings.ini"
install -Dm644 config/gtk-3.0/gtk.css "$HOME/.config/gtk-3.0/gtk.css"
install -Dm644 config/gtk-4.0/gtk.css "$HOME/.config/gtk-4.0/gtk.css"
install -Dm644 config/fontconfig/fonts.conf "$HOME/.config/fontconfig/fonts.conf"
install -Dm644 config/icons/default/index.theme "$HOME/.icons/default/index.theme"
install -Dm644 config/oh-my-zsh/custom/themes/ayu-mirage.zsh-theme "$HOME/.oh-my-zsh/custom/themes/ayu-mirage.zsh-theme"
install -Dm644 config/xdg-desktop-portal/portals.conf "$HOME/.config/xdg-desktop-portal/portals.conf"
install -Dm644 config/xdg-desktop-portal-termfilechooser/config "$HOME/.config/xdg-desktop-portal-termfilechooser/config"
install -Dm755 config/xdg-desktop-portal-termfilechooser/yazi-save-wrapper.sh "$HOME/.config/xdg-desktop-portal-termfilechooser/yazi-save-wrapper.sh"

backup "$HOME/.gtkrc-2.0"
backup "$HOME/.zshrc"
backup "$HOME/.xinitrc"
backup "$HOME/.zprofile"
backup "$HOME/.Xresources"
install -Dm644 config/gtkrc-2.0 "$HOME/.gtkrc-2.0"
install -Dm644 config/zsh/zshrc "$HOME/.zshrc"
install -Dm644 config/zsh/zprofile "$HOME/.zprofile"
install -Dm755 config/xinitrc "$HOME/.xinitrc"
install -Dm644 config/Xresources "$HOME/.Xresources"

$sudo_cmd mkdir -p /usr/share/xsessions /etc/systemd/logind.conf.d /etc/modprobe.d
cat <<EOF | $sudo_cmd tee /usr/share/xsessions/dwm.desktop >/dev/null
[Desktop Entry]
Name=dwm
Comment=dynamic window manager
Exec=$HOME/.xinitrc
Type=Application
EOF
$sudo_cmd chmod 755 /usr/share/xsessions
$sudo_cmd chmod 644 /usr/share/xsessions/dwm.desktop

cat config/logind/90-lid-hibernate.conf | $sudo_cmd tee /etc/systemd/logind.conf.d/90-lid-hibernate.conf >/dev/null
cat config/modprobe.d/processor-thermal.conf | $sudo_cmd tee /etc/modprobe.d/processor-thermal.conf >/dev/null

if command -v greetd >/dev/null 2>&1; then
	$sudo_cmd mkdir -p /etc/greetd
	cat config/greetd/config.toml | $sudo_cmd tee /etc/greetd/config.toml >/dev/null
	$sudo_cmd systemctl disable sddm.service lightdm.service display-manager.service >/dev/null 2>&1 || :
	$sudo_cmd systemctl mask lightdm.service >/dev/null 2>&1 || :
	$sudo_cmd systemctl enable greetd.service >/dev/null 2>&1 || :
	echo "Installed. greetd is enabled for next boot."
else
	echo "Installed. greetd not found — log in and run: startx"
fi
echo "Open the music player with Super+m; the bar uses mpd/mpc when available."
