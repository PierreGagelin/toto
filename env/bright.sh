#/usr/bin/env bash

set -eu

function syslog()
{
    logger $1
}

#
# Display help for this command
#
function display_usage()
{
    syslog "Usage: $0 <level>"
    syslog "COMMAND:"
    syslog "- level: decimal brightness level to set between 0 and 1"
}

#
# Update brightness for a specific output
# - $1: output name
# - $2: brightness level
#
function update_brightness()
{
    count=$(xrandr -q | grep -c "$1 connected")
    if [ $count -eq 1 ]
    then
        xrandr --output $1 --brightness $2
    fi
}

#
# Verify input
#
if [ $# -ne 1 ]
then
    syslog "Error: one an only one argument allowed"
    display_usage
    exit 1
fi

#update_brightness "LVDS-1" $1
update_brightness "HDMI-1" $1
