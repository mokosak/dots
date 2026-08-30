## install

Arch, official repos only:

```sh
./install.sh
```

Installs the packages, keeps the sources in `~/.local/src/dots` and builds dwm, dmenu, st and dwmblocks into `~/.local`,
then installs the scripts to `~/.local/bin` and the configs to `~/.config`.
Anything it replaces is backed up once as `<file>.bak-larbs`.

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

## uninstall

there's no uninstaller, because i don't plan on uninstalling.

## credits

based on [LARBS](https://github.com/LukeSmithxyz/LARBS) by Luke Smith. thanks Luke.
