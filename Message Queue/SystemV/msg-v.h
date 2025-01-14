#ifndef __msg_v__
#define __msg_v__

#define MSG_SIZE 256

// 消息结构
struct msg_buffer {
    long msg_type; // 消息类型
    char msg_text[MSG_SIZE]; // 消息内容
};

enum {
    ALL_EVENT = 0,
    CUSTOM_EVENT1 = 1,
    CUSTOM_EVENT2,
    CUSTOM_EVENT3,
};



#endif