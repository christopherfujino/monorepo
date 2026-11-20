#!/usr/bin/env bash
set -exuo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

./tool/fetch-deps.sh
./tool/setup-ocaml.sh
./tool/build-all.sh
