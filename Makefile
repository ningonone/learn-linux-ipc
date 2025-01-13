# 定义变量
CC = gcc
CFLAGS = -Wall -g
SRC_DIRS = Pipe Semaphore SharedMemory Signal Socket

# 查找所有的 .c 文件
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
# 生成对应的 .o 文件
OBJS = $(SRCS:.c=.o)
# 所有的可执行文件
EXES = $(patsubst %.c,%,$(SRCS))


clean:
	rm -f $(OBJS)
	rm -f $(EXES)

.PHONY: clean