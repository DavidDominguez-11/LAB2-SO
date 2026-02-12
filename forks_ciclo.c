#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Inicio - PID: %d\n\n", getpid());
    
    for (int i = 0; i < 4; i++) {
        fork();
    }
    
    printf("Proceso PID: %d\n", getpid());
    
    sleep(1);
    return 0;
}