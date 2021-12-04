#!/bin/bash

interval=0

# load colors!
. ~/.config/PHDWM/bar/nord

cpu() {
	cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

	printf "^c$black^ ^b$orange^  CPU"
	printf "^c$white^ ^b$black^ $cpu_val"
}

sound() {
  volume=$(pamixer --get-volume-human)
  muted=${volume::-1}
  if [ "$muted" == "mute" ]; then
    printf "^c$black^ ^b$red^ 婢 VOL"
  else
    if [ "$muted" -lt "25" ]; then
      printf "^c$black^ ^b$green^ 奄 VOL"
    elif [ "$muted" -lt "50" ]; then
      printf "^c$black^ ^b$green^ 奔 VOL"
    else
      printf "^c$black^ ^b$green^ 墳 VOL"
    fi
  fi
  printf "^c$white^ ^b$black^ %s" "$volume"
}

pkg_updates() {
	updates=$(checkupdates | wc -l)   # arch , needs pacman contrib

	if [ "$updates" == "0" ]; then
		printf "^c$green^  Fully Updated"
	else
		printf "^c$red^  $updates"" updates"
	fi
}

mem() {
	printf "^c$black^ ^b$pink^  MEM"
	printf "^c$white^ ^b$black^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
  printf "^c$black^ ^b$yellow^  ETH";
	case "$(cat /sys/class/net/en*/operstate 2>/dev/null)" in
	up) printf "^c$white^ ^b$black^ Connected";;
	down) printf "^c$white^ ^b$black^ Disconnected";;
	esac
}

clock() {
	printf "^c$black^ ^b$blue^ "
	printf "^c$white^ ^b$black^ $(date '+%I:%M %p') "
}

song() {
  playing=$(playerctl status)
  if [ "$playing" != "Playing" ]; then
    cur_song="Nothing Playing"
  else
    cur_song=$(playerctl metadata --format '{{title}} | {{artist}}')
  fi
  printf "^c$black^ ^b$blue^  SONG"
  printf "^c$white^ ^b$black^ $cur_song"
}

while true; do

	[ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
	interval=$((interval + 1))

	#sleep 1 && xsetroot -name "$updates $(battery) $(brightness) $(cpu) $(mem) $(wlan) $(clock)"
  sleep 1 && xsetroot -name "$updates $(song) $(wlan) $(cpu) $(mem) $(sound) $(clock)"
done
