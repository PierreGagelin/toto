#!/usr/bin/env sh

#
# This file is meant to install the requirement for this project
#

# fail on any error or undefined variable
set -eu

#
# Docker environment
#

OS_RELEASE=$(. /etc/os-release && echo $ID)

# install dependencies
sudo apt update
sudo apt install -y apt-transport-https
sudo apt install -y ca-certificates
sudo apt install -y curl
sudo apt install -y gnupg-agent
sudo apt install -y software-properties-common

# add Docker GPG key
curl https://download.docker.com/linux/$OS_RELEASE/gpg | sudo apt-key add -

# add Docker repository
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/$OS_RELEASE $(lsb_release -cs) stable"

# add docker group
sudo addgroup docker || echo "Ignoring error, group may already exists"

# add current user to docker group (if not, root priviledges are required to run docker commands)
sudo gpasswd --add $USER docker

# install Docker
sudo apt update
sudo apt install -y docker-ce
sudo apt install -y docker-ce-cli
sudo apt install -y containerd.io
sudo apt install -y docker-compose

# load the group (instead, one can log out and log back in)
newgrp docker
