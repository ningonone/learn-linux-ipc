CC = gcc
CFLAGS = -Wall -g
TARGET = $(patsubst %.c,%,$(wildcard *.c))

all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) *.o