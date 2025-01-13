#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    char *fifo = FIFO_NAME;
    char buffer[BUFFER_SIZE];

    if (access(fifo, F_OK) == -1) {
        if (mkfifo(fifo, 0666) == -1) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    } 

    fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        printf("Send Message: ");
        if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            // 移除换行符
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strcmp(buffer, "exit") == 0) {
                break;
            }
            write(fd, buffer, strlen(buffer) + 1);
        }
    }

    close(fd);

    return 0;
}