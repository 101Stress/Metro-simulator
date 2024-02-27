TARGET = metro-simulator

SOURCES = main.c dijkstra.c

CC = gcc

CFLAGS = -Wall -Werror

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)