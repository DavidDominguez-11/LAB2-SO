#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid1, pid2, pid3;
    clock_t inicio, fin;
    double tiempo;

    inicio = clock();   // Inciso g

    pid1 = fork();

    if (pid1 == 0) {  // PROCESO HIJO

        pid2 = fork();

        if (pid2 == 0) {  // PROCESO NIETO

            pid3 = fork();

            if (pid3 == 0) {  // PROCESO BISNIETO
                for (int i = 0; i < 1000000; i++) {
                }
            } else {  // NIETO exclusivamente
                for (int i = 0; i < 1000000; i++) {
                }
                wait(NULL);  // espera al bisnieto
            }

        } else {  // HIJO exclusivamente
            for (int i = 0; i < 1000000; i++) {
            }
            wait(NULL);  // espera al nieto
        }

    } else {  // PADRE exclusivamente
        wait(NULL);  // espera al hijo

        fin = clock();   // Inciso k

        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("Tiempo: %f\n", tiempo);
    }

    return 0;
}
