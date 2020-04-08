#!/bin/bash

picom &
/bin/bash ~/Program/dwm/scripts/dwm-status.sh &
/bin/bash ~/Program/dwm/scripts/tap-to-click.sh &
/bin/bash ~/Program/dwm/scripts/inverse-scroll.sh &
/bin/bash ~/Program/dwm/scripts/wp-autochange.sh &
sleep 1
nm-applet &
flameshot &
sleep 1
xmodmap ~/.Xmodmap &
sleep 2
fcitx &
