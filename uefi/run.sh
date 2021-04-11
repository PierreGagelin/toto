#!/usr/bin/env bash

# Forbid error and undefined variable
set -e
set -u

# Set EDK environment up
function edk_setup()
{
    local dir_build="/workspace/build"
    local edk_release="edk2-stable202102"
    local edk_artifacts=()

    edk_artifacts+=("edk2-stable202102.zip")
    edk_artifacts+=("submodule-BaseTools-Source-C-BrotliCompress-brotli.zip")
    edk_artifacts+=("submodule-CryptoPkg-Library-OpensslLib-openssl.zip")
    edk_artifacts+=("submodule-MdeModulePkg-Library-BrotliCustomDecompressLib-brotli.zip")
    edk_artifacts+=("submodule-RedfishPkg-Library-JsonLib-jansson.zip")
    edk_artifacts+=("submodule-SoftFloat.zip")
    edk_artifacts+=("submodule-UnitTestFrameworkPkg-Library-CmockaLib-cmocka.zip")

    # Note: directory can't be deleted because it's a mount, so we can't simply use rm
    find "${dir_build}" -mindepth 1 -delete

    for artifact in "${edk_artifacts[@]}"
    do
        echo "Downloading artifact=${artifact}"
        curl -s -o "${dir_build}/${artifact}" -L "https://github.com/tianocore/edk2/releases/download/${edk_release}/${artifact}"

        echo "Extracting artifact=${artifact}"
        unzip -q -d "${dir_build}" "${dir_build}/${artifact}"
    done

    # Build EDK base tools
    echo "Building EDK base tools"
    make -C /workspace/build/BaseTools > /dev/null 2>&1

    # Source EDK build environment
    cd "${dir_build}"
    ln -sf /workspace/src/TotoPkg TotoPkg
    cd - > /dev/null

    echo "Finished to set EDK environment up"
}

# Build UEFI toto package
function toto_build()
{
    local dir_build="/workspace/build"
    local opt_list=()

    # Source EDK build environment
    cd "${dir_build}"
    set +u
    source edksetup.sh > /dev/null
    set -u
    cd - > /dev/null

    opt_list+=("-a" "X64")
    opt_list+=("-t" "GCC5")
    opt_list+=("-b" "RELEASE")
    opt_list+=("-p" "TotoPkg/toto.dsc")

    # Build EDK
    echo "Building UEFI toto package"
    build "${opt_list[@]}" > /dev/null

    echo "Finished to build UEFI toto package"
}

function qemu_run()
{
    local dir_build="/workspace/build"
    local opt_list=()

    rm -rf "${dir_build}/disk"
    mkdir -p "${dir_build}/disk/efi/boot"

    cp "${dir_build}/Build/TotoPkg/RELEASE_GCC5/X64/Toto.efi" "${dir_build}/disk/efi/boot/bootx64.efi"

    opt_list+=("-bios" "/usr/share/qemu/OVMF.fd")
    opt_list+=("-hdb" "fat:rw:${dir_build}/disk")

    qemu-system-x86_64 "${opt_list[@]}"
}

if [ ${#} -ne 1 ]
then
    echo "Failed to run, need 1 argument" 1>&2
    exit 1
fi

if [ "${1}" == "setup" ]
then
    edk_setup
elif [ "${1}" == "build" ]
then
    toto_build
elif [ "${1}" == "qemu" ]
then
    qemu_run
fi
