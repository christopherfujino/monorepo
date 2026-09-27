CC = bear --append -- clang
C_VERSION = c23
AR = llvm-ar
_CHECK = `{sh -c '[ -n "$PROJECT" ] || { echo "Error: PROJECT is not set." >&2; exit 1; }'}
DEBUG_FLAGS = -g -O0 $DEBUG_FLAGS
CFLAGS = $DEBUG_FLAGS \
				-std=$C_VERSION \
				-Wall -Werror -Wextra -Wpedantic \
				-I$PWD/include \
				$CFLAGS
LDFLAGS = $LDFLAGS
DEPFILES = `{/bin/sh -c 'find . -name "*.d"'}

$PROJECT.exe: bin/main.o lib/lib$PROJECT.a
	$CC $LDFLAGS $prereq -o $target

<|cat $DEPFILES /dev/null

run:V: $PROJECT.exe
	"./${PROJECT}.exe"

bin/%.o: bin/%.c
	$CC $CFLAGS \
		-MT $target -MMD -MP -MF bin/$stem.d \
		-c bin/$stem.c -o $target

lib/%.o: lib/%.c
	$CC $CFLAGS \
		-MT $target -MMD -MP -MF lib/$stem.d \
		-c lib/$stem.c -o $target

# Downstream must add prereqs
lib/lib$PROJECT.a:
	$AR rcs $target $prereq

clean:V:
	rm -rf *.exe *.d *.o *.a compile_commands.json
	(cd bin && rm -f *.d *.o *.a)
	(cd lib && rm -f *.d *.o *.a)

# vim: ft=make
