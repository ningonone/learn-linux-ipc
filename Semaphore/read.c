#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "sem-v.h"

void sem_wait(int semid, int sem_num) {
    struct sembuf sb = {sem_num, -1, 0};
    (semid, &sb, 1);semop
}

void sem_signal(int semid, int sem_num) {
    struct sembuf sb = {sem_num, 1, 0};
    semop(semid, &sb, 1);
}


int main() {
    int shm_id = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    int sem_id = semget(SEM_KEY, 2, 0666);
    if (sem_id == -1) {
        perror("semget failed");
        exit(1);
    }

    while (1) {
        sem_wait(sem_id, 1);  // 等待信号量 1，表示可以读取

        printf("Received: %s", shm_ptr);
        sem_signal(sem_id, 0);  // 发送信号量 0，表示可以写入

        if (strncmp(shm_ptr, "exit", 4) == 0) {
            break;
        }
    }

    shmdt(shm_ptr);
    return 0;
}
