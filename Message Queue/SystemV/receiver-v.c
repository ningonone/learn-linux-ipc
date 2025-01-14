#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg-v.h"


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

    //接收
    while (1) {
        if (msgrcv(msgid, &message, sizeof(message.msg_text), CUSTOM_EVENT2, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("Receiver: %s\n", message.msg_text);
    }

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
