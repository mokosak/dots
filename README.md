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

## uninstall

there's no uninstaller, because i don't plan on uninstalling.

## credits

based on [LARBS](https://github.com/LukeSmithxyz/LARBS) by Luke Smith. thanks Luke.
