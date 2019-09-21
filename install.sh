#!/usr/bin/env sh

#
# script to set a Docker environment up
#

# fail on any error or undefined variable
set -eu

# uninstall old versions of Docker
sudo apt remove -y docker
sudo apt remove -y docker-engine
sudo apt remove -y docker.io
sudo apt remove -y containerd
sudo apt remove -y runc

# install dependencies
sudo apt update
sudo apt install -y apt-transport-https
sudo apt install -y ca-certificates
sudo apt install -y curl
sudo apt install -y gnupg-agent
sudo apt install -y software-properties-common

# add Docker GPG key
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

# add Docker repository
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

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
