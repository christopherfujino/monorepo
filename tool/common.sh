#!/usr/bin/env bash

if [[ -z "$ROOT" ]]; then
  echo 'Do not invoke this library directly!' >&2
  exit 42
fi

if command -v opam >/dev/null; then
  eval $(opam env --switch=default-switch)
fi

# 9base install path on Ubuntu
export PATH="$PATH:/usr/lib/plan9/bin"
export IMAGE_NAME=monorepo-actions-local-test
export OCAML_SWITCH=default-switch

cd "$ROOT"
