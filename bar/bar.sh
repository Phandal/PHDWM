#!/bin/bash

interval=0

# load colors!
. ~/.config/PHDWM/bar/nord

cpu() {
	cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

	printf "^c$black^ ^b$green^  CPU"
	printf "^c$white^ ^b$grey^ $cpu_val"
}

pkg_updates() {
	updates=$(checkupdates | wc -l)   # arch , needs pacman contrib

	if [ "$updates" == "0" ]; then
		printf "^c$green^  Fully Updated"
	else
		printf "^c$green^  $updates"" updates"
	fi
}

mem() {
	printf "^c$black^ ^b$red^  MEM"
	printf "^c$white^ ^b$grey^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
  printf "^c$black^ ^b$yellow^  ETH";
	case "$(cat /sys/class/net/eth0/operstate 2>/dev/null)" in
	up) printf "^c$white^ ^b$grey^ Connected";;
	down) printf "^c$white^ ^b$grey^ Disconnected";;
	esac
}

clock() {
	printf "^c$black^ ^b$blue^ "
	printf "^c$white^ ^b$grey^ $(date '+%I:%M %p') "
}

while true; do

	[ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
	interval=$((interval + 1))

	#sleep 1 && xsetroot -name "$updates $(battery) $(brightness) $(cpu) $(mem) $(wlan) $(clock)"
  sleep 1 && xsetroot -name "$updates $(wlan) $(cpu) $(mem) $(clock)"
done
