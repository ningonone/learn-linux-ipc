#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "msg-v.h"


int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // 创建唯一的
    key = ftok("progfile", 65); // 生成唯一的键 
    msgid = msgget(key, 0666 | IPC_CREAT); // 创建消息队列
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }


    while (1) {
        printf("Send: \n");
        printf("Type: ");
        if(scanf("%ld", &message.msg_type) == -1) {
            perror("scanf");
        }
        while (getchar() != '\n'); //清空输入缓冲区
        printf("Message: ");
        if (fgets(message.msg_text, MSG_SIZE, stdin) != NULL ) {
            message.msg_text[strcspn(message.msg_text, "\n")] = '\0';
            if (strcmp(message.msg_text, "exit") == 0) {
                break;
            }
            if(msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
                perror("msgsnd");
            }
        }   
    } 

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
