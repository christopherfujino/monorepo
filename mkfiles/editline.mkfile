MKSHELL = bash
# If you get a warning, it's cos you're building from a different relative
# path.
_REPO_ROOT_DEFAULT = `{realpath "$PWD/../.."}
REPO_ROOT = `{echo "${REPO_ROOT:-${_REPO_ROOT_DEFAULT}}"}
EDITLINE_ROOT = $REPO_ROOT/3p/editline
EDITLINE_LIB = $EDITLINE_ROOT/src/.libs/libeditline.a
CFLAGS = $CFLAGS -I$EDITLINE_ROOT/include

$EDITLINE_LIB:
	set -euo pipefail
	echo "REPO_ROOT = ${REPO_ROOT}"
	cd "${REPO_ROOT}/3p"
	CFLAGS='' mk editline.stamp

# vim: ft=make
