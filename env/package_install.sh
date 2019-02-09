#!/usr/bin/env sh

set -eu

sudo apt update
sudo apt upgrade

# essentials
sudo apt install -y vim
sudo apt install -y bash-completion
sudo apt install -y tree

# dev minimal tools
sudo apt install -y git
sudo apt install -y gitk
sudo apt install -y pkg-config
sudo apt install -y cmake
sudo apt install -y gcc
sudo apt install -y g++
sudo apt install -y python3
sudo apt install -y python3-pip
sudo apt install -y valgrind
sudo apt install -y lcov
sudo apt install -y cppcheck
sudo apt install -y net-tools

# dev libraries
sudo apt install -y python3-tk
python3 -m pip install pylint
python3 -m pip install zmq
python3 -m pip install protobuf
python3 -m pip install robotframework
