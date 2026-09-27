#ifndef __MONOREPO_SRC_REPO_REPL_INCLUDE_COMMON_H
#define __MONOREPO_SRC_REPO_REPL_INCLUDE_COMMON_H

#include <stddef.h> // size_t

static const char *commandList[] = {"sync "};
constexpr size_t commandListLength = sizeof(commandList) / sizeof(char *);

#endif // __MONOREPO_SRC_REPO_REPL_INCLUDE_COMMON_H
