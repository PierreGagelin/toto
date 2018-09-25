
# If not running interactively, don't do anything
case $- in
    *i*)
        ;;
    *)
        return
        ;;
esac

EDITOR=vim

# Enable programmable completion features
if ! shopt -oq posix
then
    if [ -f /usr/share/bash-completion/bash_completion ]
    then
        source /usr/share/bash-completion/bash_completion
    elif [ -f /etc/bash_completion ]
    then
        source /etc/bash_completion
    fi
fi

# Don't put duplicate lines or lines starting with space in the history
HISTCONTROL=ignoreboth

# Append to the history file, don't overwrite it
shopt -s histappend

# For setting history length see HISTSIZE and HISTFILESIZE in bash
HISTSIZE=1000
HISTFILESIZE=2000

# Check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# PS1 customization
GIT_PS1_SHOWDIRTYSTATE=1
PS1='\[\033[01;34m\]\w\[\033[00m\]\[\033[01;31m\]$(__git_ps1)\[\033[00m\] \$ '

# GNU make customization flags
if [[ ! "$MAKEFLAGS" =~ "--no-print-directory" ]]
then
    export MAKEFLAGS="$MAKEFLAGS --no-print-directory"
fi

# Alias definitions
if [ -f ~/.bash_aliases ]
then
    source ~/.bash_aliases
fi

