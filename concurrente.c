#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid1, pid2, pid3;
    clock_t inicio, fin;
    double tiempo;

    inicio = clock();

    pid1 = fork();

    if (pid1 == 0) { // Hijo

        pid2 = fork();

        if (pid2 == 0) { // Nieto

            pid3 = fork();

            if (pid3 == 0) { // Bisnieto
                for (int i = 0; i < 1000000; i++) {
                }
            } else { // Nieto
                for (int i = 0; i < 1000000; i++) {
                }
                wait(NULL);
            }

        } else { // Hijo
            for (int i = 0; i < 1000000; i++) {
            }
            wait(NULL);
        }

    } else { // Padre
        wait(NULL);
        fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo: %f segundos\n", tiempo);
    }

    return 0;
}
