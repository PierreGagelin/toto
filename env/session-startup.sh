#!/bin/bash

set -eu

# Set numerical keypad on
numlockx on

# Clear previously started processes
pkill fdpowermon || echo "No fdpowermon to kill"
pkill sleep || echo "No sleep to kill"
count=$(pgrep -c session-startup)
if [ $count -gt 1 ]
then
    for pid in $(pgrep session-startup)
    do
        if [ $pid == $$ ]
        then
            continue
        fi
        kill $pid
    done
fi

# Launch fdpowermon
fdpowermon &

# Change wallpapper indefinetely
folder=~/Pictures/wallpapers/
sleepTime=300s
while [ true ]
do
    for file in $(find "$folder" -maxdepth 1 -type f | shuf)
    do
        pcmanfm -w "$file" --wallpaper-mode=stretch
        sleep "$sleepTime" || true
    done
done
