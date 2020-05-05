#!/bin/bash
# Screenshot: http://s.natalian.org/2013-08-17/dwm_status.png
# Network speed stuff stolen from http://linuxclues.blogspot.sg/2009/11/shell-script-show-network-speed.html

print_mem(){
    memfree=$(($(grep -m1 'MemAvailable:' /proc/meminfo | awk '{print $2}') / 1024))M
    echo -e "💿 $memfree"
}

print_bat(){
    #hash acpi || return 0
    #onl="$(grep "on-line" <(acpi -V))"
    #charge="$(awk '{ sum += $1 } END { print sum }' /sys/class/power_supply/BAT*/capacity)%"
    #if test -z "$onl"
    #then
        ## suspend when we close the lid
        ##systemctl --user stop inhibit-lid-sleep-on-battery.service
        #echo -e "${charge}"
    #else
        ## On mains! no need to suspend
        ##systemctl --user start inhibit-lid-sleep-on-battery.service
        #echo -e "${charge}"
    #fi
    #echo "$(get_battery_charging_status) $(get_battery_combined_percent)%, $(get_time_until_charged )";
    echo "$(get_battery_charging_status) $(get_battery_combined_percent)%";
}

get_battery_charging_status() {
    if $(acpi -b | grep --quiet Discharging)
    then
        echo "🔋";
    else # acpi can give Unknown or Charging if charging, https://unix.stackexchange.com/questions/203741/lenovo-t440s-battery-status-unknown-but-charging
        echo "🔌";
    fi
}

get_battery_combined_percent() {
    # get charge of all batteries, combine them
    total_charge=$(expr $(acpi -b | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+ | bc));
    # get amount of batteries in the device
    battery_number=$(acpi -b | wc -l);
    percent=$(expr $total_charge / $battery_number);
    
    echo $percent;
}

print_temp(){
    test -f /sys/class/thermal/thermal_zone0/temp || return 0
    echo 🌡 $(head -c 2 /sys/class/thermal/thermal_zone0/temp)°C
}

print_date(){
    date '+%a %Y-%m-%d %H:%M'
}

LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")
export IDENTIFIER="unicode"

. "$DIR/dwmbar-functions/dwm_alsa.sh"
#. "$DIR/dwmbar-functions/dwm_backlight.sh"
#. "$DIR/dwmbar-functions/dwm_battery.sh"
#. "$DIR/dwmbar-functions/dwm_ccurse.sh"
#. "$DIR/dwmbar-functions/dwm_cmus.sh"
#. "$DIR/dwmbar-functions/dwm_countdown.sh"
#. "$DIR/dwmbar-functions/dwm_date.sh"
#. "$DIR/dwmbar-functions/dwm_keyboard.sh"
#. "$DIR/dwmbar-functions/dwm_mail.sh"
#. "$DIR/dwmbar-functions/dwm_network.sh"
#. "$DIR/dwmbar-functions/dwm_pulse.sh"
#. "$DIR/dwmbar-functions/dwm_resources.sh"
#. "$DIR/dwmbar-functions/dwm_transmission.sh"
#. "$DIR/dwmbar-functions/dwm_vpn.sh"
#. "$DIR/dwmbar-functions/dwm_weather.sh"

xsetroot -name "$(print_mem) $(dwm_alsa) $(print_bat) $(print_temp) [$(print_date)]"

exit 0

# print_volume() {
#   volume="$(amixer get Master | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')"
#   if test "$volume" -gt 0
#   then
#       echo -e "\uE05D${volume}"
#   else
#       echo -e "Mute"
#   fi
# }

# show_record(){
#   test -f /tmp/r2d2 || return
#   rp=$(cat /tmp/r2d2 | awk '{print $2}')
#   size=$(du -h $rp | awk '{print $1}')
#   echo " $size $(basename $rp)"
# }

# get_time_until_charged() {
#   # parses acpitool's battery info for the remaining charge of all batteries and sums them up
#   sum_remaining_charge=$(acpitool -B | grep -E 'Remaining capacity' | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+ | bc);
#   # finds the rate at which the batteries being drained at
#   present_rate=$(acpitool -B | grep -E 'Present rate' | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+ | bc);
#   # divides current charge by the rate at which it's falling, then converts it into seconds for `date`
#   seconds=$(bc <<< "scale = 10; ($sum_remaining_charge / $present_rate) * 3600");
#   # prettifies the seconds into h:mm:ss format
#   pretty_time=$(date -u -d @${seconds} +%T);
#   echo $pretty_time;
# }

