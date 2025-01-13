#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 256

// 消息结构
struct msg_buffer {
    long msg_type; // 消息类型
    char msg_text[MSG_SIZE]; // 消息内容
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // 创建唯一的键
    key = ftok("progfile", 65); // 生成唯一的键
    msgid = msgget(key, 0666 | IPC_CREAT); // 创建消息队列
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // 发送消息
    for (int i = 0; i < 5; i++) {
        message.msg_type = 1; // 设置消息类型
        snprintf(message.msg_text, MSG_SIZE, "Message %d", i + 1);
        msgsnd(msgid, &message, sizeof(message.msg_text), 0); // 发送消息
        printf("Sent: %s\n", message.msg_text);
        sleep(1); // 等待1秒
    }

    // 删除消息队列
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
