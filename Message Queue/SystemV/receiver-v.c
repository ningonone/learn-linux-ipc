#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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
    msgid = msgget(key, 0666 | IPC_CREAT); // 打开消息队列
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // 接收消息
    for (int i = 0; i < 5; i++) {
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0); // 接收消息
        printf("Received: %s\n", message.msg_text);
    }

    // 删除消息队列
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
