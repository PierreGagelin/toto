#!/usr/bin/env bash

#
# Install the requirements for this project
#

# Forbid error and undefined variable
set -e
set -u

function install_packages()
{
    local pkg_list=()

    pkg_list+=("docker.io")
    pkg_list+=("docker-compose")

    sudo apt install -y "${pkg_list[@]}" > /dev/null
}

install_packages

echo "TOTO INFO: Finished to install environment"
