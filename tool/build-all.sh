#!/usr/bin/env bash

set -exuo pipefail

echo "PWD = $PWD"

MKFILES=$(find -name 'mkfile')
MKFILES=($MKFILES)

for MKFILE in "${MKFILES[@]}"; do
  DIR="$(dirname "$(realpath "$MKFILE")" )"
  pushd $DIR >/dev/null
    # -k do as much work as possible in the face of errors
    mk -k
  popd >/dev/null
done
