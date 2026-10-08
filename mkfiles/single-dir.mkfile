CC = bear --append -- clang
# TODO find how to only set this if unset
C_VERSION = c23
AR = llvm-ar
_CHECK = `{sh -c '[ -n "$PROJECT" ] || { echo "Error: PROJECT is not set." >&2; exit 1; }'}
DEBUG_FLAGS = -g -O0 $DEBUG_FLAGS
CFLAGS = $DEBUG_FLAGS \
				-std=$C_VERSION \
				-Wall -Werror -Wextra -Wpedantic -Wvla \
				-I$PWD/include \
				$CFLAGS
LDFLAGS = $LDFLAGS
DEPFILES = `{/bin/sh -c 'find . -name "*.d"'}

$PROJECT.exe: main.o
	$CC $LDFLAGS $prereq -o $target

<|cat $DEPFILES /dev/null

%.o: %.c
	$CC $CFLAGS \
		-MT $target -MMD -MP -MF $stem.d \
		-c $stem.c -o $target

clean:V:
	rm -rf *.exe *.d *.o *.a compile_commands.json
	(cd bin && rm -f *.d *.o *.a)
	(cd lib && rm -f *.d *.o *.a)

# vim: ft=make
