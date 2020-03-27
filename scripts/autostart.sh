#!/bin/bash

picom &
/bin/bash ~/Program/dwm/scripts/dwm-status.sh &
/bin/bash ~/Program/dwm/scripts/tap-to-click.sh &
/bin/bash ~/Program/dwm/scripts/inverse-scroll.sh &
variety &
sleep 1
# lxappearance &
nm-applet &
flameshot &
sleep 1
xmodmap ~/.Xmodmap &
sleep 2
fcitx &
