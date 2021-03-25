#!/usr/bin/env bash

#
# Uninstall the requirements for this project
#

# Forbid error and undefined variable
set -e
set -u

function uninstall_packages()
{
    local pkg_list=()

    pkg_list+=("docker.io")
    pkg_list+=("docker-compose")

    sudo apt purge -y "${pkg_list[@]}" > /dev/null
}

uninstall_packages

echo "TOTO INFO: Finished to uninstall environment"
