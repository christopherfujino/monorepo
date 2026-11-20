#!/usr/bin/env bash
set -exuo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

GITHUB_PACKAGES=" \
  autoconf \
  $CLANG \
  cmake \
  curl \
  g++ \
  git \
  libtool \
  npm \
  ruby \
  sudo \
"

apt-get update
apt-get upgrade --yes
apt-get install --yes \
      $GITHUB_PACKAGES
