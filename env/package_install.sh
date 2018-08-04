#!/bin/sh

sudo apt update
sudo apt upgrade

sudo apt install git cmake gcc g++ libboost-dev libprotobuf-dev protobuf-compiler libzmq3-dev python3-pip vim

python3 -m pip install robotframework zmq protobuf

# Installer visual studio code en allant télécharger le package
