#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {

  char *user_input = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter programs to run \n");
    ssize_t length = getline(&user_input, &size, stdin);

    if (length == -1) {
      printf("Error!");
      break;
    }

    if ((length > 0) && (user_input[length - 1] == '\n')) {
      user_input[length - 1] = '\0';
    }

    pid_t pid = fork();

    if (pid == 0) {
      execlp(user_input, user_input, (char *)NULL);

      perror("Error: Execlp failed");
      exit(EXIT_FAILURE);
    }

    else if (pid > 0) {
      waitpid(pid, NULL, 0);
    }

    else {
      perror("Error: fork() failed \n");
    }
  }

  free(user_input);
  return 0;
}
