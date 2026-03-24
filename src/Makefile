CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LDFLAGS = -lm
TARGET = autogit
SRC = main.c AUTOGIT.c
HEADER = AUTOGIT.h
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/$(TARGET)

.PHONY: clean all install
