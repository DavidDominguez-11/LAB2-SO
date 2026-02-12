#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

#define SHM_NAME "/lab5shm"
#define SIZE 50

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Uso: %s <n> <x>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    int shm_fd;
    int created = 0;

    // Intentar crear memoria compartida
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);

    if (shm_fd == -1) {
        if (errno == EEXIST) {
            printf("%c: Shared mem obj already created\n", x);
            shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
        } else {
            perror("shm_open");
            return 1;
        }
    } else {
        printf("%c: Created new shared mem obj %d\n", x, shm_fd);
        created = 1;
        ftruncate(shm_fd, SIZE);
    }

    char *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("%c: Ptr created with value %p\n", x, ptr);

    if (created) {
        memset(ptr, 0, SIZE);
        printf("%c: Initialized shared mem obj\n", x);
    }

    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if (pid == 0) {  // HIJO

        close(pipefd[1]);

        char buffer;
        int index = 0;

        while (read(pipefd[0], &buffer, 1) > 0) {
            ptr[index++] = buffer;
        }

        close(pipefd[0]);
        munmap(ptr, SIZE);
        close(shm_fd);
        exit(0);
    }

    else {  // PADRE

        close(pipefd[0]);

        for (int i = 1; i <= SIZE; i++) {
            if (i % n == 0) {
                write(pipefd[1], &x, 1);
            }
        }

        close(pipefd[1]);
        wait(NULL);

        printf("\n%c: Shared memory has: %s\n", x, ptr);

        munmap(ptr, SIZE);
        close(shm_fd);

        return 0;
    }
}
