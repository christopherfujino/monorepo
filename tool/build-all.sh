#!/usr/bin/env bash

set -exuo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

MKFILES=$(find -name 'mkfile')
MKFILES=($MKFILES)

for MKFILE in "${MKFILES[@]}"; do
  DIR="$(dirname "$(realpath "$MKFILE")" )"
  pushd $DIR >/dev/null
    # -k do as much work as possible in the face of errors
    mk -e
  popd >/dev/null
done
