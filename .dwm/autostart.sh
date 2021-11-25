#!/bin/bash

pkill -x bar.sh
pkill -x mopidy

picom &
~/.fehbg
xset r rate 300 30
dunst &
exec mopidy &

exec ~/.config/PHDWM/.dwm/bar/./bar.sh &
exec dwm
