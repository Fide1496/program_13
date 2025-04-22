/* Problem 3 -- List the include files you need for this program. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>

#include "semun.h"
#include "binary_sem.h"

#define CHILD_SEM 0
#define PARENT_SEM 1

typedef struct {
    int num_blocks;
    struct {
        int length;
        char ch;
    } blocks[20];
} shared_data_t;

void child_process(int semid, int shmid) {
    shared_data_t *data = (shared_data_t *)shmat(shmid, NULL, 0);
    srand(time(NULL) ^ getpid());

    releaseSem(semid, CHILD_SEM);

    data->num_blocks = (rand() % 11) + 10;
    for (int i = 0; i < data->num_blocks; ++i) {
        data->blocks[i].length = (rand() % 9) + 2;
        data->blocks[i].ch = 'a' + (rand() % 26);
    }

    releaseSem(semid, PARENT_SEM);
    reserveSem(semid, CHILD_SEM);

    shmdt(data);
    releaseSem(semid, PARENT_SEM);
}

void parent_process(int semid, int shmid) {
    shared_data_t *data = (shared_data_t *)shmat(shmid, NULL, 0);
    srand(time(NULL) ^ getpid());

    reserveSem(semid, PARENT_SEM);

    int width = (rand() % 6) + 10; 
    int count = 0;

    for (int i = 0; i < data->num_blocks; ++i) {
        for (int j = 0; j < data->blocks[i].length; ++j) {
            putchar(data->blocks[i].ch);
            if (++count % width == 0) putchar('\n');
        }
    }
    if (count % width != 0) putchar('\n');

    releaseSem(semid, CHILD_SEM);
    reserveSem(semid, PARENT_SEM);

    shmdt(data);
}

int main(int argc, char *argv[]) {
    int semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    int shmid = shmget(IPC_PRIVATE, sizeof(shared_data_t), IPC_CREAT | 0666);

    if (semid == -1 || shmid == -1) {
        perror("IPC creation failed");
        exit(1);
    }

    init_sem(semid, CHILD_SEM, 1);  
    init_sem(semid, PARENT_SEM, 0); 

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        child_process(semid, shmid);
        exit(0);
    } else {
        parent_process(semid, shmid);
        wait(NULL);

        del_sem_set(semid);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
