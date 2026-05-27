# my suckless setup

> [short personal description — what this is, why you made it, vibe etc.]

![screenshot](screenshot.png)

---

## components

| component | what it does |
|-----------|-------------|
| [dwm](https://dwm.suckless.org) | window manager |
| [dmenu](https://tools.suckless.org/dmenu) | app launcher / general picker |
| [slock](https://tools.suckless.org/slock) | screen locker |
| [dwmblocks](https://github.com/torrinfail/dwmblocks) | status bar |
| picom | compositor |
| dunst | notifications |
| mpd + ncmpcpp | music player |
| greetd + tuigreet | login manager |
| kitty | terminal |
| yazi | file manager |

## theme

[Ayu Mirage](https://github.com/ayu-theme/ayu-colors) — `#1f2430` background, `#ffcc66` accent

---

## keybindings

> `Mod` = Super (Windows key)

### apps
| key | action |
|-----|--------|
| `Mod+Enter` | terminal (kitty) |
| `Mod+D` | app launcher (dmenu) |
| `Mod+B` | browser (mullvad-browser) |
| `Mod+F` | file manager (yazi) |
| `Mod+M` | music player (ncmpcpp) |
| `Mod+W` | wallpaper picker |
| `Mod+X` | lock screen (slock) |
| `Mod+Shift+E` | exit menu (lock / suspend / hibernate / logout / reboot / shutdown) |

### windows
| key | action |
|-----|--------|
| `Mod+J / K` | focus next / prev window |
| `Mod+H / L` | shrink / grow master area |
| `Mod+Z` | swap focused window with master |
| `Mod+Q` | close window |
| `Mod+Tab` | jump to previous tag |
| `Mod+Shift+Q` | quit dwm |

### tags (workspaces)
| key | action |
|-----|--------|
| `Mod+1–9` | switch to tag |
| `Mod+Ctrl+1–9` | toggle tag view |
| `Mod+Shift+1–9` | send window to tag |
| `Mod+Ctrl+Shift+1–9` | toggle window on tag |

### monitors
| key | action |
|-----|--------|
| `Mod+Left / Right` | focus monitor |
| `Mod+Shift+Left / Right` | send window to monitor |

### screenshots
| key | action |
|-----|--------|
| `Print` | fullscreen → `~/Pictures/Screenshots/` |
| `Shift+Print` | screenshot menu |
| `Mod+Shift+S` | area select with blur effect |

### media keys
| key | action |
|-----|--------|
| `XF86AudioRaiseVolume / LowerVolume` | volume ±5% |
| `XF86AudioMute` | toggle mute |
| `XF86AudioMicMute` | toggle mic mute |
| `XF86MonBrightnessUp / Down` | brightness ±5% |
| `XF86AudioPlay / Next / Prev / Stop` | media control |

### mouse
| action | result |
|--------|--------|
| `Mod+Left drag` | move window |
| `Mod+Right drag` | resize window |
| `Mod+Middle click` | toggle floating |
| click layout symbol | cycle layout |

---

## status bar

Clicks on bar segments are interactive.

| block | shows | click |
|-------|-------|-------|
| music | MPD / MPRIS track + state | left: toggle play, right: open ncmpcpp |
| network | active interface + connection | — |
| bluetooth | power state + connected device | — |
| volume | sink volume / mute | scroll: adjust, middle: mute |
| battery | charge % + status | — |
| clock | date + time | left: calendar |

---

## scripts

| script | what it does |
|--------|-------------|
| `wall` | wallpaper picker from `~/Pictures/Wallpapers/` |
| `screenshot` | fullscreen / area / menu screenshot |
| `volume` | volume control with bar signal |
| `brightness` | brightness control via brightnessctl |
| `music-control` | play/pause/next/prev for MPD and MPRIS (YouTube etc.) |
| `now-playing` | prints current track from MPD or playerctl |
| `bluetooth-menu` | dmenu bluetooth device picker |
| `bt-console` | bluetui / bluetoothctl TUI |
| `exit-menu` | dmenu power/session menu |
| `file-manager` | opens yazi, falls back to home |
| `fzf-cd` | fuzzy directory jump in a new kitty window |
| `nightlight` | automatic color temperature shift at night |
| `kb-watch` | dunst notification on keyboard layout change |
| `osd` | on-screen display helper for notifications |
| `fetch` | fastfetch with custom config |
| `term-calendar` | terminal calendar in a floating kitty window |
| `dmenu-theme` | themed dmenu wrapper used by all pickers |
| `dmenupass` | sudo password prompt via dmenu (SUDO_ASKPASS) |

---

## install

> Arch Linux (tested). Requires `yay` for AUR packages.

```sh
git clone [your repo url]
cd my-suckless-setup
./install.sh
```

The installer builds and installs dwm, dmenu, slock and dwmblocks from source,
copies all configs and scripts, and sets up greetd as the login manager.

---

## structure

```
my-suckless-setup/
├── dwm/          window manager source
├── dmenu/        launcher source
├── slock/        locker source
├── dwmblocks/    status bar source
├── scripts/      shell scripts installed to ~/.local/bin/
└── config/       dotfiles (kitty, dunst, picom, mpd, zsh, ...)
```
