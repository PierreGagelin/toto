#!/usr/bin/env bash

# Forbid error and undefined variable
set -e
set -u

function protobuf_setup()
{
    local dir_build=/tmp/build
    local dir_src=/code

    mkdir $dir_build

    cd $dir_build
    cmake $dir_src
    make
    cd -

    $dir_build/tu_toto_pb
    $dir_build/tu_toto_pb_c
    $dir_build/tu_toto_pb.py
}

protobuf_setup
