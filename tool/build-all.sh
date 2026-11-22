#!/usr/bin/env bash

set -exuo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

MKFILES=$(find -name 'mkfile')
MKFILES=($MKFILES)

for MKFILE in "${MKFILES[@]}"; do
  DIR="$(dirname "$(realpath "$MKFILE")" )"
  pushd $DIR >/dev/null
    set +e
      # -n means print the commands needed to execute the target
      mk -n ci
      HAS_CI=$?
    set -e
    if [[ HAS_CI -eq 0 ]]; then
      mk -e ci
    else
      # mk the default target
      mk -e
    fi
  popd >/dev/null
done
