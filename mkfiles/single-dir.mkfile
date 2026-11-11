MKSHELL = bash

CC = bear --append -- clang
C_VERSION = `{echo "${C_VERSION:-c23}"}
AR = llvm-ar
DEBUG_FLAGS = `{echo "${DEBUG_FLAGS:--g -O0}"}
CFLAGS = $DEBUG_FLAGS \
				-std=$C_VERSION \
				-Wall -Werror -Wextra -Wpedantic \
				-Wimplicit-fallthrough -Wvla \
				-I$PWD/include \
				$CFLAGS
LDFLAGS = $LDFLAGS
DEPFILES = `{/bin/sh -c 'find . -name "*.d"'}

$PROJECT.exe: main.o
	$CC $LDFLAGS $prereq -o $target

<|cat $DEPFILES /dev/null

# Q attribute means do not print recipe before executing
phony_check:VQ:
	set -e
	if [[ -z "$PROJECT" ]]; then
		echo "Please set the \$PROJECT variable!" 2>&1
		false
	fi

%.o: %.c
	$CC $CFLAGS \
		-MT $target -MMD -MP -MF $stem.d \
		-c $stem.c -o $target

clean:V:
	rm -rf *.exe *.d *.o *.a compile_commands.json
	(cd bin && rm -f *.d *.o *.a)
	(cd lib && rm -f *.d *.o *.a)

# vim: ft=make
