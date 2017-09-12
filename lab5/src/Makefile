TARGET = lab5
PREFIX = /usr/local/bin
CC = clang

.PHONY: all clean install uninstall

all: $(TARGET)
clean:
	rm -rf $(TARGET) *.o
lab5.o: lab5.c
	$(CC) -c -o lab5.o lab5.c
$(TARGET): lab5.o
	$(CC) -o $(TARGET) lab5.o
install:
	install -D $(TARGET) $(PREFIX)/$(TARGET)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)
