Copyright License
------------------
- I dont own the rights (License) to the font or the wallpaper. I downloaded the font from nerd fonts' official website (https://www.nerdfonts.com/) and the wallpaper from wallhaven (https://www.wallhaven.cc/). So please dont report or take down my dots.

Requirements
------------
- In order to build dwm you need the Xlib header files (libx11 libxft libxinerama).
- To be able to compile (make clean install) you also need to install base-devel package.
- To be able to use screenshot, volume and brightness controls, you need to install either "pipewire" or "pulseaudio" for volume control, "brightnessctl" for brightness control and "flameshot" for screenshots.
- In order to see special icons and have font working you need to copy Terminess Nerd Font from the directory into the /usr/local/share/fonts/ directory.
- For GTK Theme you need to install Everforest-Dark GTK Theme.


Installation
------------
Copy dwm (or mydots) to your .config directory then cd into dwm files.

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

After installing dwm you should install other programs (slstatus, st and dmenu)

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
MODKEY, F4       BRIGHTNESS DOWN
MODKEY, F5       BRIGHTNESS UP
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

GTK
---
- To be able to fully replicate this configuration, you will also need to configure your GTK theme (so other applications will share the same coloring).
- Download "Everforest-Dark" Theme (many sources, i used KDE's official website)
- Extract it and copy Everforest-Dark folder into /usr/share/themes/ (Warning: This will install it system-wide, if you want only user-wide install, copy it into ~/.themes folder.
  Command to copy: ```sudo cp -r /path/to/your/theme /usr/share/themes/```
- Install GTK changer (i recommend lxappearance) and change the theme (optionally the font too).
- I personally use "SpaceMono Nerd Font Mono" as my font and "ePapirus-Dark" as my icons.



FINAL PRODUCT
-------------
![dots](https://github.com/user-attachments/assets/11f7df7d-2df6-43ab-afbc-9089e6cd5713)

