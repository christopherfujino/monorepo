#!/usr/bin/env bash
set -euo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

set +e
  # Verify the daemon is running
  docker info >/dev/null
  EXIT=$?
set -e
if [[ $EXIT -ne 0 ]]; then
  echo 'Please start the docker daemon, `systemctl start docker.service`'
  exit $EXIT
fi

USER=ubuntu

docker container run \
  --tty \
  --interactive \
  --volume "$ROOT:/home/$USER" \
  --user "$USER" \
  --rm \
  "$IMAGE_NAME"
