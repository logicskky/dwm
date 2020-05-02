#!/bin/bash

picom &
/bin/bash ~/Programs/Softwares/dwm/scripts/dwm-status.sh &
/bin/bash ~/Programs/Softwares/dwm/scripts/tap-to-click.sh &
/bin/bash ~/Programs/Softwares/dwm/scripts/inverse-scroll.sh &
/bin/bash ~/Programs/Softwares/dwm/scripts/wp-autochange.sh &
sleep 1
nm-applet &
flameshot &
sleep 1
xmodmap ~/.Xmodmap &
sleep 2
fcitx &
