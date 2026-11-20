#!/usr/bin/env bash
set -exuo pipefail

ROOT="$(dirname "$(dirname "$(realpath "${BASH_SOURCE[0]}" )" )" )"
source "${ROOT}/tool/common.sh"

PACKAGES="\
  dune \
  ocamlformat \
"

# setup ocaml
opam init --yes --bare --disable-sandboxing
opam switch create --yes $OCAML_SWITCH 5.4.0
opam install --yes $PACKAGES
