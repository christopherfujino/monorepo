#!/usr/bin/env bash
set -exuo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

GENERAL_BUILDTOOLS="\
  9base \
  bear \
  llvm \
  llvm-dev \
"

EDITLINE_DEPS="\
  autoconf \
  libtool \
"

# TODO: remove libreadline-dev once we've removed it from sloth
OCAML_DEPS="\
  opam \
  libreadline-dev
"

# https://wiki.ubuntu.com/Raylib
RAYLIB_DEPS="\
  libxrandr-dev \
  libx11-dev \
  libxinerama-dev \
  libxcursor-dev \
  libxi-dev \
  libgl1-mesa-dev \
  libglu1-mesa-dev \
"

sudo apt-get update
sudo apt-get --yes upgrade
sudo apt-get --quiet install --yes \
  $GENERAL_BUILDTOOLS \
  $RAYLIB_DEPS \
  $OCAML_DEPS
