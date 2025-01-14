#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_queue"
#define MAX_SIZE 256

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];

    // 打开消息队列
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // 接收消息
    for (int i = 0; i < 5; i++) {
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read >= 0) {
            printf("Received: %s\n", buffer);
        } else {
            perror("mq_receive");
        }
    }

    // 关闭消息队列
    mq_close(mq);
    // 删除消息队列
    mq_unlink(QUEUE_NAME);
    return 0;
}
