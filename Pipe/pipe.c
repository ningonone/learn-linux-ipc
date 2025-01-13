#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main() 
{
    int fd[2]; 
    pid_t pid;
    char write_msg[] = "hello, is a test message";
    char read_msg[128];

    if (pipe(fd) == -1) { //创建管道,成功返回0，失败返回-1
        perror("pipe");
        return 1;
    }

    pid = fork(); //创建子进程，成功返回进程号，失败返回-1
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) { //父进程
        close(fd[1]); //通信前关闭不必要的描述符是为了防止资源泄露和竞争
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Received from parent: %s \n", read_msg);
        close(fd[0]);


    } else { //子进程
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1); //加1是为了把终止符一起传入，不然会乱码
        close(fd[1]); 
    }

    return 0;
}