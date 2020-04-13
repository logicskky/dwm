#!/bin/bash

picom &
/bin/bash ~/Program/Suckless/dwm/scripts/dwm-status.sh &
/bin/bash ~/Program/Suckless/dwm/scripts/tap-to-click.sh &
/bin/bash ~/Program/Suckless/dwm/scripts/inverse-scroll.sh &
/bin/bash ~/Program/Suckless/dwm/scripts/wp-autochange.sh &
sleep 1
nm-applet &
flameshot &
sleep 1
xmodmap ~/.Xmodmap &
sleep 2
fcitx &
