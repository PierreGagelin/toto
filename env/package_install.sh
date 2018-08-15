#!/bin/sh

sudo apt update
sudo apt upgrade

sudo apt install git cmake gcc g++ libboost-dev libprotobuf-dev protobuf-compiler libzmq3-dev python3-pip valgrind lcov vim gitk

python3 -m pip install robotframework zmq protobuf

# Visual studio code needs to be downloaded to be installed
