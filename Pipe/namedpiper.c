#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <string.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    char *fifo = FIFO_NAME;
    char buffer[BUFFER_SIZE];
    struct timeval timeout;
    fd_set read_fds;

    if (access(fifo, F_OK) == -1) {
        if (mkfifo(fifo, 0666) == -1) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    } 

    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    timeout.tv_sec = 5;  // 5秒
    timeout.tv_usec = 0; // 0微秒

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(fd, &read_fds);

        int ret = select(fd + 1, &read_fds, NULL, NULL, NULL);
        if (ret > 0 && FD_ISSET(fd, &read_fds)) {
            ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; // 添加空字符以正确结束字符串
                printf("Received: %s\n", buffer);
                if (strcmp(buffer, "exit") == 0) {
                    printf("Exiting...\n");
                    break;
                }
            } else if (bytesRead == 0) {
                // 处理EOF情况
                printf("Writer closed the pipe.\n");
                break;
            } else {
                perror("read");
                break;
            }
        }
    }

    close(fd);

    return 0;
}