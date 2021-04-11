#!/usr/bin/env bash

# Forbid error and undefined variable
set -e
set -u

# Run a container with options
function docker_run()
{
    local opt_list=()

    opt_list+=("--interactive")
    opt_list+=("--tty")
    opt_list+=("--detach")
    opt_list+=("--rm")
    opt_list+=("--name" "toto_uefi")
    opt_list+=("--hostname" "toto_uefi")
    opt_list+=("--env" "DISPLAY=${DISPLAY}")
    opt_list+=("--mount" "type=bind,src=${HOME}/dev/toto/uefi,dst=/workspace/src")
    opt_list+=("--mount" "type=bind,src=${HOME}/dev/build/toto/uefi,dst=/workspace/build")
    opt_list+=("--mount" "type=bind,src=/tmp/.X11-unix,dst=/tmp/.X11-unix")

    # Allow X11 usage to any user
    xhost + > /dev/null

    docker container run "${opt_list[@]}" toto_uefi
}

# Create the build directory
mkdir -p "${HOME}/dev/build/toto/uefi"

# Clean useless containers and images
docker image prune --force
docker container prune --force

# docker build --tag toto_uefi .

docker_run
