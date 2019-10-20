#!/usr/bin/env sh

#
# script to tear a docker environment down
#

# fail on any error or undefined variable
set -eu

# delete user from the docker group
sudo gpasswd --del $USER docker

# delete docker group
sudo delgroup docker

# delete Docker packages
sudo apt purge -y docker-ce
sudo apt purge -y docker-ce-cli
sudo apt purge -y containerd.io
sudo apt purge -y docker-compose

# delete Docker databases
sudo rm -rf /var/lib/docker

# delete Docker repository
sudo add-apt-repository --remove "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

# delete Docker GPG key
sudo apt-key del 0EBFCD88

# don't know if those should be removed, anyone else could use them
#
# sudo apt purge -y apt-transport-https
# sudo apt purge -y ca-certificates
# sudo apt purge -y curl
# sudo apt purge -y gnupg-agent
# sudo apt purge -y software-properties-common
