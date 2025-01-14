#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include "shared.h"


int main() {
    // 生成唯一键
    key_t key = ftok("shmfile", 65);
    // 获取共享内存段的标识符
    int shmid = shmget(key, SHM_SIZE, 0666);
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

    // 读取数据
    printf("Reader: Read from shared memory: %s\n", str);

    // 分离共享内存
    if (shmdt(str) == -1) {
        perror("shmdt");
        exit(1);
    }

    // 删除共享内存段
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
