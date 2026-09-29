TARGET=l5
CC=clang
CFLAGS= -O3
LDFLAGS=
SRCS=main.c src/counter.c
OBJS=$(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJS) $(TARGET)
