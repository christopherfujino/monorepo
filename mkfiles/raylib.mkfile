RAYLIB_ROOT = `{realpath "$PWD/../../3p/raylib"}
RAYLIB_BUILD = $RAYLIB_ROOT/build
RAYLIB_INCLUDE = $RAYLIB_BUILD/raylib/include
RAYLIB_LIBRARY = $RAYLIB_BUILD/raylib/libraylib.a
CFLAGS = $CFLAGS -I$RAYLIB_INCLUDE

$RAYLIB_LIBRARY:
	set -euo pipefail
	cd "$RAYLIB_ROOT/.." # 3p root
	CFLAGS="" mk raylib.stamp

# vim: ft=make
