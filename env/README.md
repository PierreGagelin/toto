# What
Here are some of my configuration files I like

# How
These are to be copied at their respective places. It can vary between OS

# List of files
## package\_install.sh
A script to install every packages I generally use

## settings.json
User settings for Visual Studio Code. For Linux, it's to be put in $HOME/.config/Code/User/

## .bashrc
## .bash\_aliases
## .vimrc
## .gitconfig
Configuration files for bash, vim and git. To be put in $HOME/

## sysctl.conf
Configuration file for sysctl, to be put in /etc/

## session-startup.sh
## session-startup.desktop
Two files to customize the session startup:
- session-startup.desktop: LXDE application to put under $HOME/.config/autostart/. It just starts session-startup.sh
- session-startup.sh: bash script to put under $HOME/Documents/scripts/. When called it does:
    - lock numeric keypad
    - run power management utility (display battery level)
    - rotate wallpapers each 5 minutes

## bright.sh
Script based on xrandr to update monitor's brightness. This isn't by default on LXDE
