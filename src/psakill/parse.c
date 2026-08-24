#include "parse.h"

#include <stdlib.h> // abort(), atoi()
#include <string.h> // strncmp()

ParsedLine handleLine(const char *line) {
  int i = 0;
  while (line[i] == ' ') {
    i++;
  }

  // check for header
  if (strncmp(line + i, "PID", 3) == 0) {
    return (ParsedLine){.pid = 0, .cmd = nullptr};
  }

  // parse PID
  int pid = 0;
  while (line[i] >= '0' && line[i] <= '9') {
    pid *= 10;
    pid += line[i] - '0';
    i++;
  }

  while (line[i] == ' ') {
    i++;
  }

  // parse cmd
  int len = 0;
  while (line[i + len] != '\n') {
    len++;
  }
  char *cmd = malloc(len + 1);
  strncpy(cmd, line + i, len);
  cmd[i + len] = '\0';

  return (ParsedLine){
      .pid = pid,
      .cmd = cmd,
  };
}
