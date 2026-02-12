#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        execl("./ipc", "ipc", "3", "a", NULL);
    } 
    else {
        execl("./ipc", "ipc", "4", "b", NULL);
    }

    return 0;
}
