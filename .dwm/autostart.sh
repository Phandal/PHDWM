#!/bin/bash

picom &
~/.fehbg
xset r rate 300 30
dunst &

pkill -x bar.sh
exec ~/.config/PHDWM/.dwm/bar/./bar.sh &
exec dwm
