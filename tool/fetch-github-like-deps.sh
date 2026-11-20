#!/usr/bin/env bash
set -exuo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

# we're using clang-21 on lenovo ubuntu
CLANG_VERSION='21'
CLANG="clang-$CLANG_VERSION"

GITHUB_PACKAGES=" \
  autoconf \
  $CLANG \
  cmake \
  curl \
  g++ \
  git \
  libtool \
  ninja-build \
  npm \
  ruby \
  sudo \
"

apt-get update
apt-get upgrade --yes
apt-get install --yes \
      $GITHUB_PACKAGES
