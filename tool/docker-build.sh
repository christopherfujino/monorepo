#!/usr/bin/env bash
set -euo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

DOCKER_CONTEXT="${ROOT}/.empty-docker-context"
mkdir "$DOCKER_CONTEXT" || true

docker image build "$DOCKER_CONTEXT" \
  --tag "$IMAGE_NAME" \
  --file "${ROOT}/Dockerfile" \
  --rm

docker image prune --force
