_DUMMY = `{sh -c '[ -n "$PROJECT" ] || { echo "Error: PROJECT is not set." >&2; exit 1; }'}
# If you get a warning, it's cos you're building from a different relative
# path. TODO: figure out how to allow callers to set their own var
_REPO_ROOT_DEFAULT = `{realpath "$PWD/../.."}
# TODO
REPO_ROOT = `{echo "${REPO_ROOT:-${_REPO_ROOT_DEFAULT}}"}
EDITLINE_ROOT = $REPO_ROOT/3p/editline
EDITLINE_LIB = $EDITLINE_ROOT/src/.libs/libeditline.a
CFLAGS = $CFLAGS -I$EDITLINE_ROOT/include
#LDFLAGS = -l:$EDITLINE_LIB $LDFLAGS

$EDITLINE_LIB:
	set -euo pipefail
	echo "REPO_ROOT = ${REPO_ROOT}"
	cd "${REPO_ROOT}/3p"
	CFLAGS='' mk editline.stamp

# vim: ft=make
