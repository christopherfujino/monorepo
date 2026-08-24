#ifndef __PSAKILL_PARSE_H
#define __PSAKILL_PARSE_H

typedef struct ParsedLine {
  int pid;
  const char *cmd;
} ParsedLine;

ParsedLine handleLine(const char *line);

#endif // __PSAKILL_PARSE_H
