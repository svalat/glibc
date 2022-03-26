#!/bin/bash

#-----------------------------------
# If fail due to deps, you can call:
#
# sudo apt-get build-dep glibc
#
#-----------------------------------

################################################################################
set -e
set -x
set -u

################################################################################
# glibc version
LIBC_ABI_VERSION='6'
GLIBC_VERSION='2.31'
# get dir
SCRIPT_DIR=$(realpath $(dirname $0))
# patch dir
PATCH_DIR_OFFICAL="${SCRIPT_DIR}/patches-ioinstr-${GLIBC_VERSION}-official"
PATCH_DIR_DEBIAN="${SCRIPT_DIR}/patches-ioinstr-${GLIBC_VERSION}-debian-11"

################################################################################
function setup_workdir()
{
	# rm if present
	rm -rfd workdir
	# create dir
	mkdir -p workdir
}

################################################################################
function fetch_sources()
{
	# get sources
	apt-get source glibc
}

################################################################################
function build_offical_source_git()
{
	# extract orig sources
	mkdir glibc-${GLIBC_VERSION}-orig
	tar -xf glibc_${GLIBC_VERSION}.orig.tar.xz  -C glibc-${GLIBC_VERSION}-orig

	#move into
	pushd glibc-${GLIBC_VERSION}-orig/glibc-${GLIBC_VERSION}/

	# create git
	git init
	git add .
	git commit -m "official/${GLIBC_VERSION}"
	git branch "official/${GLIBC_VERSION}"

	# apply patches on official
	git checkout -b patched/ioinstr-${GLIBC_VERSION}
	for patch in ${PATCH_DIR_OFFICAL}/*
	do
		git am ${patch}
	done

	#restore to workdir
	popd
}

################################################################################
function build_debian_source_git()
{
	# build official git
	git init
	git add .
	git commit -m "debian/${GLIBC_VERSION}"
	git checkout -b "debian/${GLIBC_VERSION}"	
}

################################################################################
function gen_rebased_branch()
{
	# move
	git checkout -b "debian/rebased-${GLIBC_VERSION}"

	# fetch orig
	git remote add origin ../glibc-${GLIBC_VERSION}-orig/glibc-${GLIBC_VERSION}/
	git fetch --all

	# rebase
	git rebase -X theirs origin/official/${GLIBC_VERSION}
}

################################################################################
function return_to_debian_official()
{
	# return on official
	git checkout debian/${GLIBC_VERSION}
}

################################################################################
function build_debian_ioinstr_patched()
{
	# return on official
	git checkout -b debian/ioinstr-${GLIBC_VERSION}

	# patch debian scripts
	echo "Apply patch ${SCRIPT_DIR}/debian-deb-patch-${GLIBC_VERSION}.diff"
	patch -p1 < "${SCRIPT_DIR}/debian-deb-patch-${GLIBC_VERSION}.diff"
	git add debian
	git commit -m "debian/ioinstr-patched"

	# copy patches
	cp -r "${PATCH_DIR_DEBIAN}" "debian/patches/all/"
	echo >> debian/patches/series
	for patch in ${PATCH_DIR_DEBIAN}/*
	do
		echo all/$(basename ${PATCH_DIR_DEBIAN})/$(basename $patch) >> debian/patches/series
	done

	# save
	git add debian
	git commit -m "debian/ioinstr-add-patches"
}

################################################################################
function source_configure()
{
	# prepare and configure
	#DEB_BUILD_PROFILES="nobiarch" debuild --no-lintian -us -uc -d
	DEB_BUILD_PROFILES="nobiarch" dpkg-source --before-build .
	#DEB_BUILD_PROFILES="nobiarch" dpkg-source -b .
	DEB_BUILD_PROFILES="nobiarch" fakeroot debian/rules clean
	DEB_BUILD_PROFILES="nobiarch" dpkg-source --build .
	DEB_BUILD_PROFILES="nobiarch" fakeroot debian/rules build || echo "Expected error (TODO check how to avoid) !"
}

################################################################################
function source_build()
{
	# build
	make -C build-tree/amd64-libc/ -j
}

################################################################################
function copy_built_libc()
{
	# copy
	rm -rfd "${SCRIPT_DIR}/libc-ioinstr"
	mkdir -p "${SCRIPT_DIR}/libc-ioinstr"
	cp "${SCRIPT_DIR}/workdir/glibc-${GLIBC_VERSION}/build-tree/amd64-libc/libc.so.${LIBC_ABI_VERSION}" "${SCRIPT_DIR}/libc-ioinstr/libc-ioinstr.so.${LIBC_ABI_VERSION}"
	ln -s "${SCRIPT_DIR}/libc-ioinstr.so.${LIBC_ABI_VERSION}" "${SCRIPT_DIR}/libc-ioinstr/libc.so.${LIBC_ABI_VERSION}"
}

################################################################################
setup_workdir
pushd workdir
fetch_sources
build_offical_source_git
# move to dir
pushd glibc-${GLIBC_VERSION}
build_debian_source_git
gen_rebased_branch
return_to_debian_official
build_debian_ioinstr_patched
source_configure
source_build
copy_built_libc

################################################################################
echo ">>>> DONE <<<<<"
