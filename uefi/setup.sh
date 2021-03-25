#!/usr/bin/env bash

# Forbid error and undefined variables
set -e
set -u

# Build bootloader
build -p TotoPkg/toto.dsc -a X64 -b RELEASE -t GCC5 -D TPM20
echo "TOTO_INFO: Built bootloader"

# Create a UEFI disk
dd if=/dev/zero of="$HOME"/Documents/disk.img bs=100M count=1 > /dev/null 2>&1
echo "TOTO_INFO: Created disk"

# Setup loop device
sudo losetup -P /dev/loop0 "$HOME"/Documents/disk.img
echo "TOTO_INFO: Set loop device up"

# Create GUID partition table
sudo sfdisk /dev/loop0 > /dev/null << EOF
label: gpt
device: /dev/loop0

/dev/loop0p1 : size=40MB, type=C12A7328-F81F-11D2-BA4B-00A0C93EC93B
/dev/loop0p2 : size=40MB, type=0FC63DAF-8483-4772-8E79-3D69D8477DE4
EOF
echo "TOTO_INFO: Created GUID partition table"

# Format first partition to FAT32
sudo mkfs.fat /dev/loop0p1 > /dev/null
echo "TOTO_INFO: Formatted UEFI partition"

# Mount disk
mkdir -p /tmp/mydisk
sudo mount /dev/loop0p1 /tmp/mydisk
echo "TOTO_INFO: Mounted disk"

# Add bootloader to disk
sudo mkdir -p /tmp/mydisk/efi/boot
sudo cp /home/pir/dev/edk2/Build/TotoPkg/RELEASE_GCC5/X64/Toto.efi /tmp/mydisk/efi/boot/bootx64.efi
echo "TOTO_INFO: Added bootloader to disk"

# Dismount disk
sync
sudo umount /tmp/mydisk
echo "TOTO_INFO: Dismounted disk"

# Tear loop device down
sudo losetup -d /dev/loop0
echo "TOTO_INFO: Tore loop device down"

mkdir -p /tmp/mytpm0

# Run software TPM
SWTPM_CMD="swtpm socket"
SWTPM_CMD="$SWTPM_CMD --daemon"
SWTPM_CMD="$SWTPM_CMD --tpm2"
SWTPM_CMD="$SWTPM_CMD --tpmstate dir=/tmp/mytpm0"
SWTPM_CMD="$SWTPM_CMD --ctrl type=unixio,path=/tmp/mytpm0/swtpm-sock"
SWTPM_CMD="$SWTPM_CMD --log level=20"
$SWTPM_CMD
echo "TOTO_INFO: Ran software TPM"

# Run QEMU
QEMU_CMD="qemu-system-x86_64"
QEMU_CMD="$QEMU_CMD -bios /usr/share/ovmf/OVMF.fd"
QEMU_CMD="$QEMU_CMD -drive file=$HOME/Documents/disk.img,format=raw"
QEMU_CMD="$QEMU_CMD -chardev socket,id=chrtpm,path=/tmp/mytpm0/swtpm-sock"
QEMU_CMD="$QEMU_CMD -tpmdev emulator,id=tpm0,chardev=chrtpm"
QEMU_CMD="$QEMU_CMD -device tpm-tis,tpmdev=tpm0"
QEMU_CMD="$QEMU_CMD -enable-kvm"
QEMU_CMD="$QEMU_CMD -cpu host"
$QEMU_CMD
echo "TOTO_INFO: Ran QEMU"

# Destroy UEFI disk
rm "$HOME"/Documents/disk.img
echo "TOTO_INFO: Destroyed UEFI disk"
