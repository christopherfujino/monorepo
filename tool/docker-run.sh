#!/usr/bin/env bash
set -euo pipefail

set +e
  # Verify the daemon is running
  docker info >/dev/null
  EXIT=$?
set -e
if [[ $EXIT -ne 0 ]]; then
  echo "Please start the docker daemon"
  exit $EXIT
fi


