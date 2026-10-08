CC = bear --append -- clang
# TODO find how to only set this if unset
C_VERSION = c23
AR = llvm-ar
DEBUG_FLAGS = -g -O0 $DEBUG_FLAGS
CFLAGS = $DEBUG_FLAGS \
				-std=$C_VERSION \
				-Wall -Werror -Wextra -Wpedantic -Wvla \
				-I$PWD/include \
				$CFLAGS
LDFLAGS = $LDFLAGS
DEPFILES = `{/bin/sh -c 'find . -name "*.d"'}
MKSHELL = bash

$PROJECT.exe: bin/main.o lib/lib$PROJECT.a
	$CC $LDFLAGS $prereq -o $target

<|cat $DEPFILES /dev/null

phony_check:V:
	set -e
	if [[ -z "$PROJECT" ]]; then
		echo "Please set the \$PROJECT variable!" 2>&1
		false
	fi

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
lib/lib$PROJECT.a: phony_check
	_ARGS=""
	for arg in $prereq; do
		if [[ $arg != 'phony_check' ]]; then
			_ARGS="$arg $_ARGS"
		fi
	done
	$AR rcs $target $_ARGS

clean:V:
	rm -rf *.exe *.d *.o *.a compile_commands.json
	(cd bin && rm -f *.d *.o *.a)
	(cd lib && rm -f *.d *.o *.a)

# vim: ft=make
