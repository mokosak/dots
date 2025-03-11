Requirements
------------
- In order to build dwm you need the Xlib header files.
- In order to see special icons and have font working you need to copy JetBrainsMono Nerd Font from the dwm directory into the /usr/local/share/fonts/ directory.


Installation
------------
Copy dwm (or mydots) to your .config directory then cd into dwm files.

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

KeyStrokes
----------
```
MODKEY, D        DMENU
MODKEY, ENTER    ST
MODKEY, T        TOGGLE DWM BAR
MODKEY, J        CHANGE FOCUSED WINDOW +1
MODKEY, K        CHANGE FOCUSED WINDOW -1
MODKEY, I        HORIZONTAL / VERTICAL WINDOWS CHANGE +1
MODKEY, U        HORIZONTAL / VERTICAL WINDOWS CHANGE -1
MODKEY, H        CHANGE MASTER WINDOW LENGTH +1
MODKEY, L        CHANGE MASTER WINDOW LENGTH -1
MODKEY, Z        SWITCH MASTER WINDOW
MODKEY, Q        KILL PROGRAM
MODKEY|SHIFT,Q   KILL DWM
MODKEY|SHIFT,E   EXITDWM MENU
MODKEY, F3       UP VOLUME (pactl required)
MODKEY, F2       DOWN VOLUME (pactl required)
MODKEY, F1       MUTE VOLUME (pactl required)
MODKEY|SHIFT,S   SCREENSHOT (flameshot package required)
```

.xinitrc
--------
```
picom --daemon &
slstatus &
pulseaudio -D &
nitrogen --restore &
dwm
```

