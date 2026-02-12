#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Inicio - PID: %d\n\n", getpid());
    
    fork();
    fork();
    fork();
    fork();
    
    printf("Proceso PID: %d\n", getpid());
    
    sleep(1);
    return 0;
}