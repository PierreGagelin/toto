#!/usr/bin/env sh

set -eu

#
# This file is optional, it installs and configures my favorite packages
#

sudo apt update
sudo apt install -y vim
sudo apt install -y bash-completion
sudo apt install -y tree
sudo apt install -y gitk
sudo apt install -y net-tools

# Visual Studio Code (vscode)
PKG_KEY="/usr/share/keyrings/packages.microsoft.gpg"
PKG_SRC="deb [arch=amd64 signed-by=$PKG_KEY] https://packages.microsoft.com/repos/vscode stable main"

curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > /tmp/packages.microsoft.gpg
sudo install -o root -g root -m 644 /tmp/packages.microsoft.gpg $PKG_KEY

echo $PKG_SRC | sudo tee /etc/apt/sources.list.d/vscode.list

sudo apt update
sudo apt install -y code

#
# Configuration
#

cp bashrc $HOME/.bashrc
cp bash_aliases $HOME/.bash_aliases
cp gitconfig $HOME/.gitconfig
cp vimrc $HOME/.vimrc
cp settings.json $HOME/.config/Code/User/settings.json
