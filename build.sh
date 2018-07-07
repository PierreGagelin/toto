#!/bin/bash

# Script to build the toto project
# Works with relative path

DIR_SOURCE=$(dirname $_)
DIR_BUILD="$DIR_SOURCE/build"

ACTION_BUILD="false"
ACTION_CLEAN="false"


# Exit on error or undefined variable
set -eu


function action_build
{
    mkdir -p $DIR_BUILD

    # Could use cmake's -H and -B options but it's undocumented so better not rely on those
    cd $DIR_BUILD
    cmake ../
    cd -

    make -C $DIR_BUILD -j 2
}


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


while getopts "bch" opt
do
    case "${opt}" in
        b)
            ACTION_BUILD="true"
            ;;
        c)
            ACTION_CLEAN="true"
            ;;
        h)
            echo "lol, t'as cru un peu, non ?"
            ;;
        *)
            echo "Invalid option" >&2
            ;;
    esac
done


if [ $ACTION_CLEAN = "true" ]
then
    action_clean
fi


if [ $ACTION_BUILD = "true" ]
then
    action_build
fi

