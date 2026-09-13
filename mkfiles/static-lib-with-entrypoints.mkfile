CC = clang
C_VERSION = gnu99
AR = llvm-ar
_DUMMY = `{ /usr/bin/bash -c "set -u; $PROJECT" }
_CHECK = `{sh -c '[ -n "$MY_VAR" ] || { echo "Error: MY_VAR is not set." >&2; exit 1; }'}
DEBUG_FLAGS = -g -O0
CFLAGS = $DEBUG_FLAGS \
				-std=$C_VERSION \
				-Wall -Werror -Wextra -Wpedantic \
				-I$PWD/include
LDFLAGS =
DEPFILES = `{/bin/sh -c 'find . -name "*.d"'}

run:V: $PROJECT.exe
	echo success
	#"./${PROJECT}.exe"

<|cat $DEPFILES /dev/null

$PROJECT.exe: bin/main.o lib/lib$PROJECT.a
	$CC $LDFLAGS $prereq -o $target

bin/%.o: bin/%.c
	$CC $CFLAGS \
		-MT $target -MMD -MP -MF bin/$stem.d \
		-c bin/$stem.c -o $target

lib/%.o: lib/%.c
	$CC $CFLAGS \
		-MT $target -MMD -MP -MF lib/$stem.d \
		-c lib/$stem.c -o $target

lib/lib$PROJECT.a: lib/mod1.o
	$AR rcs $target $prereq

clean:V:
	rm -rf *.exe *.d *.o *.a compile_commands.json
	(cd bin && rm -f *.d *.o *.a)
	(cd lib && rm -f *.d *.o *.a)

# vim: ft=make
