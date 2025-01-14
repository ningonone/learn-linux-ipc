#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include "shared.h"


int main() {
    // 创建共享内存段
    key_t key = ftok("shmfile", 65); // 生成唯一键
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // 将共享内存段映射到进程地址空间
    char *str = (char *)shmat(shmid, NULL, 0);
    if (str == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // 写入数据到共享内存
    strcpy(str, "Hello, Shared Memory!");
    printf("Writer: Wrote to shared memory: %s\n", str);

    // 分离共享内存
    if (shmdt(str) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
