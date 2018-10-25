#!/bin/bash

#
# Script to build the toto project
#

# Project directories
DIR_SCRIPT=$(dirname $0)
DIR_CMD=$(pwd)
DIR_SOURCE=$DIR_CMD/$DIR_SCRIPT
DIR_BUILD=$DIR_SOURCE/../build

# Exit on error or undefined variable
set -eu

# Customize toto
TOTO_CPP="OFF"
TOTO_FACTORY="OFF"
TOTO_JSON="OFF"
TOTO_PROTOBUF="OFF"
TOTO_ZMQ="OFF"

# Customize cmake
CMAKE_BUILD_TYPE="Debug"

# Action to do
ACTION_BUILD="false"
ACTION_CLEAN="false"
ACTION_INSTALL="false"
ACTION_TEST="false"

#
# Build the project
#
function action_build
{
    mkdir -p $DIR_BUILD

    # Could use cmake's -H and -B options but it's undocumented so better not rely on those
    cd $DIR_BUILD
    cmake $CMAKE_OPTION $DIR_SOURCE
    cd -

    make -C $DIR_BUILD
}

#
# Clean the build directory
#
function action_clean
{
    if [ ! -d $DIR_BUILD ]
    then
        echo "Nothing to clean, directory does not exist [dir=$DIR_BUILD]"
        return 0
    fi

    # Clean objects, libraries and executables
    make -C $DIR_BUILD clean
}

#
# Install required packages
#
function action_install
{
    wget --directory-prefix=/tmp/ https://github.com/protocolbuffers/protobuf/releases/download/v3.6.1/protobuf-cpp-3.6.1.tar.gz
    wget --directory-prefix=/tmp/ https://github.com/protobuf-c/protobuf-c/releases/download/v1.3.1/protobuf-c-1.3.1.tar.gz

    tar -C /tmp/ -xzf /tmp/protobuf-cpp-3.6.1.tar.gz
    tar -C /tmp/ -xzf /tmp/protobuf-c-1.3.1.tar.gz

    cd /tmp/protobuf-3.6.1
    CFLAGS=-O2 CXXFLAGS="-std=c++11 -O2" ./configure
    make -j 4
    sudo make install
    cd -

    cd /tmp/protobuf-c-1.3.1
    CFLAGS=-O2 CXXFLAGS="-O2" ./configure
    make -j 4
    sudo make install
    cd -
}

#
# Run the tests
#
function action_test
{
    make -C $DIR_BUILD test
}

#
# Retrieve command line options
#
while getopts "AB:CFJPZbchit" option
do
    case $option in
        A)
            TOTO_CPP="ON"
            TOTO_FACTORY="ON"
            TOTO_JSON="ON"
            TOTO_PROTOBUF="ON"
            TOTO_ZMQ="ON"
            ;;
        B)
            CMAKE_BUILD_TYPE=$OPTARG
            ;;
        C)
            TOTO_CPP="ON"
            ;;
        F)
            TOTO_FACTORY="ON"
            ;;
        J)
            TOTO_JSON="ON"
            ;;
        P)
            TOTO_PROTOBUF="ON"
            ;;
        Z)
            TOTO_ZMQ="ON"
            ;;
        b)
            ACTION_BUILD="true"
            ;;
        c)
            ACTION_CLEAN="true"
            ;;
        i)
            ACTION_INSTALL="true"
            ;;
        t)
            ACTION_TEST="true"
            ;;
        h)
            echo "lol, t'as cru un peu, non ?"
            ;;
        *)
            echo "Invalid option" >&2
            ;;
    esac
done

# Build options
CMAKE_OPTION=
CMAKE_OPTION="$CMAKE_OPTION -DCMAKE_BUILD_TYPE:STRING=$CMAKE_BUILD_TYPE"
CMAKE_OPTION="$CMAKE_OPTION -DTOTO_CPP:BOOL=$TOTO_CPP"
CMAKE_OPTION="$CMAKE_OPTION -DTOTO_FACTORY:BOOL=$TOTO_FACTORY"
CMAKE_OPTION="$CMAKE_OPTION -DTOTO_JSON:BOOL=$TOTO_JSON"
CMAKE_OPTION="$CMAKE_OPTION -DTOTO_PROTOBUF:BOOL=$TOTO_PROTOBUF"
CMAKE_OPTION="$CMAKE_OPTION -DTOTO_ZMQ:BOOL=$TOTO_ZMQ"

#
# Execute actions
#
if [ $ACTION_INSTALL = "true" ]
then
    action_install
fi

if [ $ACTION_CLEAN = "true" ]
then
    action_clean
fi

if [ $ACTION_BUILD = "true" ]
then
    action_build
fi

if [ $ACTION_TEST = "true" ]
then
    action_test
fi
