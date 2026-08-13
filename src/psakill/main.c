#include <ncurses.h>  // addstr(), addch(), refresh()
#include <stdlib.h>   // exit()
#include <sys/wait.h> // waitpid()
#include <unistd.h>   // dup2(), fork()

void render(void) {
  initscr();
  addstr("Hello, ");
  addch(A_ALTCHARSET | ACS_LTEE);
  addch(A_ALTCHARSET | ACS_RTEE);
  addch(A_ALTCHARSET | ACS_BTEE);
  addch(A_ALTCHARSET | ACS_TTEE);
  addch(A_ALTCHARSET | ACS_HLINE);
  addch(A_ALTCHARSET | ACS_VLINE);
  addch(A_ALTCHARSET | ACS_LLCORNER);
  addch(A_ALTCHARSET | ACS_LRCORNER);
  addch(A_ALTCHARSET | ACS_PI);
  refresh();
  getch();
  endwin();
}

int main(void) {
  // render();
  int pipefd[2];
  {
    if (pipe(pipefd) != 0) {
      perror("pipe(2) failed!");
      exit(1);
    }
  }
  int pipe_read = pipefd[0];
  int pipe_write = pipefd[1];
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork(2) failed!");
    exit(1);
  }
  if (pid == 0) {
    close(pipe_read);
    int fd = dup2(pipe_write, STDOUT_FILENO);
    if (fd == -1) {
      char msg[BUFSIZ];
      snprintf(msg, BUFSIZ - 1, "Failure calling dup2(%d, %d)", pipe_write,
               STDOUT_FILENO);
      perror(msg);
      abort();
    }
    // BSD options, a means all procs with a tty
    execlp("ps", "a", "--format", "pid,command", NULL);
    perror("execlp(3) failed!");
    exit(1);
  }

  // Parent
  close(pipe_write);

  size_t bufsize = 0;
  char *buffer = NULL;
  FILE *file_read = fdopen(pipe_read, "r");
  int i = 1;
  while (1) {
    ssize_t n = getline(&buffer, &bufsize, file_read);
    if (n == -1) {
      fprintf(stderr, "EOF or error!\n");
      break;
    }
    printf("[%3d] %s", i++, buffer);
  }

  pid_t res = waitpid(pid, NULL, 0x0);
  if (res == -1) {
    perror("waitpid(2) failed!");
    exit(1);
  }
  printf("Parent done.\n");
}
