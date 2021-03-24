#!/usr/bin/env bash

#
# This file is optional, it installs and configures my favorite packages
#

# Forbid error and undefined variables
set -e
set -u

#
# Install some packages
#
function install_packages()
{
    local pkg_list=()
    local tmp_dir=

    pkg_list+=("vim")
    pkg_list+=("bash-completion")
    pkg_list+=("tree")
    pkg_list+=("git")
    pkg_list+=("gitk")

    sudo apt install -y "${pkg_list[@]}" > /dev/null
    echo "TOTO INFO: Installed Debian packages"

    tmp_dir=$(mktemp -d)
    curl --silent -L "https://code.visualstudio.com/sha/download?build=stable&os=linux-deb-x64" --output "${tmp_dir}"/code.deb > /dev/null
    sudo apt install -y "${tmp_dir}"/code.deb > /dev/null
    rm -r "${tmp_dir}"
    echo "TOTO INFO: Installed Visual Studio Code"
}

install_packages

#
# Configuration
#

cp bashrc "${HOME}"/.bashrc
cp bash_aliases "${HOME}"/.bash_aliases
cp gitconfig "${HOME}"/.gitconfig
cp vimrc "${HOME}"/.vimrc

mkdir -p "${HOME}"/.config/Code/User
cp keybindings.json "${HOME}"/.config/Code/User
cp settings.json "${HOME}"/.config/Code/User
echo "TOTO INFO: Configured packages"
