CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -pthread

TARGET = httpserver

SOURCES = httpserver.c queue.c log.c cacher.c


OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
