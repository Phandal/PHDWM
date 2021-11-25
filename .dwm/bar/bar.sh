#!/bin/bash

interval=0

# load colors!
#. ~/.dwm/bar/themes/onedark

cpu() {
	cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

	printf " CPU "
	printf "$cpu_val"
}

pkg_updates() {
	updates=$(checkupdates | wc -l)   # arch , needs pacman contrib

	if [ "$updates" == "0" ]; then
		printf " Fully Updated"
	else
		printf " $updates"" updates"
	fi
}

mem() {
	printf " "
	printf "$(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
	case "$(cat /sys/class/net/eth0/operstate 2>/dev/null)" in
	up) printf " %s" " Connected" ;;
	down) printf " %s" " Disconnected" ;;
	esac
}

clock() {
	printf " "
	printf "$(date '+%I:%M %p') "
}

while true; do

	[ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
	interval=$((interval + 1))

	#sleep 1 && xsetroot -name "$updates $(battery) $(brightness) $(cpu) $(mem) $(wlan) $(clock)"
  sleep 1 && xsetroot -name "$updates | $(cpu) | $(mem) | $(wlan) | $(clock)"
done
