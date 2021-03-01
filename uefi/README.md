# UEFI test

This directory hosts an example of how to build a UEFI application that uses a software TPM through QEMU

## Software TPM through QEMU

Install QEMU :

- sudo apt install -y qemu-system-x86

Install swtpm :

- download archive <https://github.com/stefanberger/swtpm/releases>
- sudo apt update
- sudo apt install -y automake
- sudo apt install -y autoconf
- sudo apt install -y coreutils
- sudo apt install -y expect
- sudo apt install -y libtool
- sudo apt install -y sed
- sudo apt install -y net-tools
- sudo apt install -y python3
- sudo apt install -y python3-twisted
- sudo apt install -y trousers
- sudo apt install -y tpm-tools
- sudo apt install -y build-essential
- sudo apt install -y devscripts
- sudo apt install -y equivs
- sudo apt install -y libssl-dev
- sudo apt install -y pkg-config
- sudo apt install -y libtasn1-6-dev
- sudo apt install -y gawk
- sudo apt install -y socat
- sudo apt install -y python3-pip
- sudo apt install -y libseccomp-dev
- download and install <https://packages.debian.org/sid/libtpms0>
- download and install <https://packages.debian.org/sid/libtpms-dev>
- ./autogen.sh
- ./configure --prefix=/usr
- make
- make check
- sudo make install

Run QEMU with the software TPM

- mkdir /tmp/mytpm0
- swtpm socket --tpm2 --tpmstate dir=/tmp/mytpm0 --ctrl type=unixio,path=/tmp/mytpm0/swtpm-sock --log level=20
- qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -chardev socket,id=chrtpm,path=/tmp/mytpm0/swtpm-sock -tpmdev emulator,id=tpm0,chardev=chrtpm -device tpm-tis,tpmdev=tpm0

You should see a Tcg2 protocol appear after boot. This can be inspected with a UEFI shell

Note that OVMF.fd needs to have support for TPM device. It is the case for the one provided in /usr/share/ovmf.

## TODO

- add a section to describe how to setup EDKII to build TotoPkg
