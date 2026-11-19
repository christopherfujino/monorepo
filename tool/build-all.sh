#!/usr/bin/env bash

set -exuo pipefail

MKFILES=$(find -name 'mkfile')
MKFILES=($MKFILES)

for MKFILE in "${MKFILES[@]}"; do
  DIR="$(dirname "$(realpath "$MKFILE")" )"
  pushd $DIR >/dev/null
    # -k do as much work as possible in the face of errors
    #mk -k
    mk
  popd >/dev/null
done
