#!/usr/bin/env sh

set -eu

DIR_BUILD=/tmp/build
DIR_SRC=/code

mkdir $DIR_BUILD

cd $DIR_BUILD
cmake $DIR_SRC
make
cd -

$DIR_BUILD/tu_toto_pb
$DIR_BUILD/tu_toto_pb_c
$DIR_BUILD/tu_toto_pb.py
