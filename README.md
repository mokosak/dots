## install

Debian or Arch, official repos only:

```sh
./install.sh
```

Installs the packages, keeps the sources in `~/.local/src/dots` and builds dwm, dmenu, st and dwmblocks into `~/.local`,
then installs the scripts to `~/.local/bin` and the configs to `~/.config`.
Anything it replaces is backed up once as `<file>.bak-larbs`.

- Debian starts ibus (an input-method service) at login, and ibus keeps
  forcing the keyboard back to a single layout, so the installer turns it
  off for your user (`im-config -n none`, written to `~/.xinputrc`). If you
  had already picked an input method there, it's left alone.
- With a login screen (GDM, LightDM...), dwm is added as a session: log out,
  pick "dwm" (the gear icon on GDM) and log in. GNOME or whatever else you
  had stays as it was.
- Without one, `startx` on tty1 runs it through `~/.xinitrc`.
- Debian has no Iosevka package; if the font isn't installed yet, the
  official release is downloaded into `~/.local/share/fonts`.
- Debian's mpd package starts a system-wide mpd; the installer turns that off
  because yours runs per user.

## keybinds (mod = super)

| key | does |
|-----|------|
| `mod+enter` | terminal (st) |
| `mod+d` | launcher (dmenu) |
| `mod+b` | browser |
| `mod+m` | music (ncmpcpp) |
| `mod+n` | RSS (newsboat) |
| `mod+r` | file manager (Thunar) |
| `mod+shift+w` | network (nmtui) |
| `mod+x` | lock |
| `mod+shift+e` | system menu: lock, leave/renew dwm, sleep, hibernate, reboot, shutdown |
| `mod+j` / `k` | focus down / up |
| `mod+h` / `l` | shrink / grow master |
| `mod+o` / `mod+shift+o` | more / fewer windows in master |
| `mod+z` | zoom to master |
| `mod+q` / `mod+shift+q` | kill window / quit dwm |
| `mod+shift+f` | fullscreen |
| `mod+shift+space` | toggle floating |
| `mod+s` | sticky (window shows on every tag) |
| `mod+shift+b` | toggle bar |
| `mod+space` | toggle last two layouts (tile and floating at first) |
| `mod+t` / `f` / `u` / `i` | tile / floating / monocle / centered master |
| `mod+[1-9]` | view tag (`+shift` move window, `+ctrl` toggle) |
| `mod+0` / `mod+shift+0` | view all tags / window on all tags |
| `mod+tab` | previous tag |
| `mod+left` / `right` | focus monitor (`+shift` move window) |
| `print` | screenshot, full screen |
| `mod+shift+s` | screenshot, select an area |
| `shift+print` | screenshot menu (window, copy to clipboard...) |
| `mod+minus` / `equal` | volume down / up |
| `mod+shift+m` | mic mute |
| `mod+p` | play / pause |
| `mod+comma` / `period` | previous / next track |
| media keys | volume, mic, playback, brightness |

Mouse: `mod+drag` moves, `mod+right-drag` resizes, `mod+middle-click` floats.
Status blocks are clickable: the clock shows the month, music opens ncmpcpp,
volume opens pulsemixer, scrolling changes volume or brightness, and so on.
Shift+click opens a block's script in `$EDITOR`.

Notifications are clickable: left click runs the notification's action (a
message opens its chat and dwm jumps there; with several actions, a dmenu
lets you pick), middle click opens that menu (actions and links), right click
dismisses. `(A)` marks ones with actions.

Screenshots go to `~/Pictures/Screenshots` (`$SCREENSHOT_DIR` overrides).

## games

A fullscreen game can sit on one tag while you work on another:

- Games stay parked off-screen while their tag isn't shown, even if they
  re-request fullscreen or resize themselves.
- A fullscreen window ignores its own resize requests, so games can't shrink
  themselves out of fullscreen.
- picom unredirects fullscreen windows: no compositor latency in-game.
- `mod+shift+f` forces fullscreen for games that only offer borderless.
- If a new window opens on the game's *own* tag, the game leaves fullscreen
  so that window isn't hidden behind it. Keep Steam/Discord on another tag.
- Steam and its games (`steam_app_*`) never swallow a terminal.

## system tray

- left click: dwm goes to the app's tag and focuses its window, even for apps
  that ignore left clicks themselves. If the app has no window open
  (closed to the tray), the click goes to the app, which reopens it
- right click: the app's own menu, dropping down under the icon

When an app asks for focus (a tray click, "Show" in its tray menu, a link
opening in the browser), dwm switches to it, unless a fullscreen window has
focus: then the app's tag is only marked urgent, so games stay put. Set
`focusonactivate = 0` in dwm/config.h for stock dwm (always just urgent).

It's the suckless systray patch with these bugs fixed:
- it told every icon a modal dialog was open, so GTK apps ignored all clicks
- it said the tray was vertical, so menus opened sideways over the bar
- it sent icons a malformed "you're docked" message
- it could crash when another tray was running
- it forced icons back on screen whenever an app hid its own, which could
  make dwm and that app fight in a loop and lag the whole machine. Now an
  icon is shown or hidden only when its app asks.

## st

| key | does |
|-----|------|
| mouse wheel | scroll history, 3 lines (in less/man/vim it scrolls the program) |
| `shift+pageup/down`, `alt+k/j`, `alt+u/d` | scroll history |
| highlight with the mouse | copies: `ctrl+v` in any program, or middle-click |
| `ctrl+shift+c` / `alt+c` | copy |
| `ctrl+shift+v` / `alt+v` / `shift+insert` | paste |
| `alt+l` / `alt+y` | open / copy a URL on screen (dmenu) |
| `alt+o` | copy a command's output (dmenu) |
| `ctrl+shift+k/j` (or `pageup/down`) | bigger / smaller font, `ctrl+shift+home` resets |
| `alt+s` / `alt+a` | more / less transparent |

Typing while scrolled up jumps back to the prompt.

## status bar

dwmblocks: music, unread RSS, memory, CPU temp,
network traffic (click: nmtui, for Wi-Fi and connections), volume,
brightness, battery, keyboard layout, clock, bluetooth. Blocks with nothing
to show (no battery on a desktop, etc.) stay hidden.

mpd (music) starts on demand, when ncmpcpp (`mod+m`) or a music key connects
to it, and only listens on this machine; until then the music block stays
empty.

Click the Bluetooth block for bluetuith, a Bluetooth TUI (pair, connect,
audio profiles, file transfer; its keys are listed along the bottom), in
gruvbox. Middle click turns Bluetooth on or off. It isn't packaged for
Debian, so the installer fetches the pinned release and checks its SHA-256.

The keyboard block shows the active layout and a click switches to the next
one. It changes the moment the layout does: `xkblayout -w` (a tiny helper
built with dwmblocks) runs from `~/.xinitrc` and pokes the block on every
switch. For more than one layout, add `setxkbmap -layout ...` to `~/.xinitrc`.

## lock screen and viewers

`xss-lock` (started from `~/.xinitrc`) runs `slock` before every suspend or
hibernate, lid included, and after 10 minutes idle; `xset s 1800` in
`~/.xinitrc` makes that 30. Videos, calls and games pause the idle timer:
`screensaver-inhibit` provides the "keep the screen on" service GNOME used
to, and while an app uses it the bar shows ☕ (right click: which app). An
app that quits or crashes lets go automatically.

PDFs open in zathura, dark by default (`i` shows the original colors, `d`/`u`
half pages, `J`/`K` zoom), and images in nsxiv. Both are gruvbox, and the
installer makes them the defaults for files you open from Firefox or Thunar.

## theme

Everything is in `~/.config/x11/xresources`: the bar (`dwm.*`), dmenu
(`dmenu.*`) and st (`*.color0..15`). The bar has its own keys, so a new
terminal palette can't repaint it. After editing, run
`xrdb -merge ~/.config/x11/xresources` and use system menu > renew dwm.
On a HiDPI screen, uncomment `Xft.dpi` there.

Gruvbox dark throughout: the bar is `#1d2021` with the active tag in green
`#98971a`, the focused window gets a `#005577` frame and unfocused ones blend
into the wallpaper, dmenu highlights in `#83a598`, and st is 73% opaque over
the wallpaper.

Fonts come from `ttc-iosevka`: Iosevka Term Light in st (Iosevka's cut made
for terminals, so arrows and symbols stay one cell wide) and Iosevka
everywhere else. Iosevka ships its own monochrome clock faces and a few other
symbols, so `~/.config/fontconfig/conf.d/60-iosevka-color-emoji.conf` hides
those from it and the bar's icons all stay color emoji.

GTK apps use [jmattheis/gruvbox-dark-gtk](https://github.com/jmattheis/gruvbox-dark-gtk)

## uninstall

there's no uninstaller, because i don't plan on uninstalling.

## credits

based on [LARBS](https://github.com/LukeSmithxyz/LARBS) by Luke Smith. thanks Luke.
