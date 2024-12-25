CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
TARGET = autogit
SRC = main.c AUTOGIT.c
HEADER = AUTOGIT.h

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean all