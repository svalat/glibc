#!/bin/bash

#-----------------------------------
# If fail due to deps, you can call:
#
# sudo apt-get build-dep glibc
#
#-----------------------------------


set -e
set -x

# get dir
SCRIPT_DIR=$(realpath $(dirname $0))

# rm if present
rm -rfd workdir

# create dir
mkdir -p workdir
pushd workdir

# get sources
apt-get source glibc

# move to dir
pushd glibc-2.28

# apply patch
patch -p0 < "${SCRIPT_DIR}/debian-deb-patch-2.28.diff"
cp "${SCRIPT_DIR}/ioinstr-2.28-2.33.diff" "debian/patches/all/ioinstr.diff"

# build
DEB_BUILD_PROFILES="nobiarch" debuild -us -uc

# move back
popd

# extract
ar x libc6_2.28-10_amd64.deb
tar -xvf data.tar.xz

# copy
mkdir -p "${SCRIPT_DIR}/libc-ioinstr"
cp "lib/x86_64-linux-gnu/libc-2.28.so" "${SCRIPT_DIR}/libc-ioinstr/libc-ioinstr.so.6"
ln -s "libc-ioinstr.so.6" "${SCRIPT_DIR}/libc-ioinstr/libc.so.6"
