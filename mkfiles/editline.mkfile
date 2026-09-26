# If you get a warning, it's cos you're building from a different relative
# path. TODO: figure out how to allow callers to set their own var
REPO_ROOT = `{realpath "$PWD/../.."}
EDITLINE_ROOT = $REPO_ROOT/3p/editline
EDITLINE_LIB = $EDITLINE_ROOT/src/.libs/libeditline.a
CFLAGS = -I$EDITLINE_ROOT/include $CFLAGS
_CHECK = `{sh -c '[ -n "$PROJECT" ] || { echo "Error: PROJECT is not set." >&2; exit 1; }'}

$EDITLINE_LIB:
	false # TODO

# vim: ft=make
