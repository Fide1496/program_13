#include <sys/sem.h>
#include <errno.h>
// #include "binary_sem.h"

// Options for semaphore operations
int bsUseSemUndo = 1;
int bsRetryOnEintr = 1;

// Internal helper to get the flags
static int get_sem_flags() {
    return bsUseSemUndo ? SEM_UNDO : 0;
}

int initSemAvailable(int semId, int semNum) {
    union semun {
        int val;
    } arg;
    arg.val = 1;
    return semctl(semId, semNum, SETVAL, arg);
}

int initSemInUse(int semId, int semNum) {
    union semun {
        int val;
    } arg;
    arg.val = 0;
    return semctl(semId, semNum, SETVAL, arg);
}

int reserveSem(int semId, int semNum) {
    struct sembuf op;
    op.sem_num = semNum;
    op.sem_op = -1;
    op.sem_flg = get_sem_flags();

    while (semop(semId, &op, 1) == -1) {
        if (errno != EINTR || !bsRetryOnEintr)
            return -1;
    }
    return 0;
}

int releaseSem(int semId, int semNum) {
    struct sembuf op;
    op.sem_num = semNum;
    op.sem_op = 1;
    op.sem_flg = get_sem_flags();

    return semop(semId, &op, 1);
}

int del_sem_set(int semId) {
    return semctl(semId, 0, IPC_RMID);
}

int init_sem(int semId, int semNum, int value) {
    if (value == 0) {
        return initSemInUse(semId, semNum);
    } else {
        return initSemAvailable(semId, semNum);
    }
}
