#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_queue"
#define MAX_SIZE 256

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];

    // 设置消息队列属性
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // 最大消息数
    attr.mq_msgsize = MAX_SIZE; // 最大消息大小
    attr.mq_curmsgs = 0;

    // 创建消息队列
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // 发送消息
    for (int i = 0; i < 5; i++) {
        snprintf(buffer, MAX_SIZE, "Message %d", i + 1);
        mq_send(mq, buffer, strlen(buffer) + 1, 0); // +1 for null terminator
        printf("Sent: %s\n", buffer);
        sleep(1); // 等待1秒
    }

    // 关闭消息队列
    mq_close(mq);
    return 0;
}
