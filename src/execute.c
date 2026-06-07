#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int execute_command(char *argv[]) {

    int status;
    time_t start= time(NULL);
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execvp(argv[0], argv);

        perror("execvp execution failed");
        exit(1);
    }
    else {

        waitpid(pid, &status, 0);
        time_t end= time(NULL);
        printf("Time taken: %ld seconds\n", (end-start));
        if (WIFEXITED(status)) {
            // printf("Child process exited with status: %d\n", WEXITSTATUS(status));
            return WEXITSTATUS(status);
        }

    }
    return -1;
}

