TARGET = lab4
PREFIX = /usr/local/bin
CC = clang

.PHONY: all clean install uninstall

all: $(TARGET)
clean:
	rm -rf $(TARGET) *.o
lab4.o: lab4.c
	$(CC) -c -o lab4.o lab4.c
pr_a.o: pr_a.c
	$(CC) -c -o pr_a.o pr_a.c
pr_b.o: pr_b.c
	$(CC) -c -o pr_b.o pr_b.c
$(TARGET): lab4.o pr_a.o pr_b.o
	$(CC) -o $(TARGET) lab4.o pr_a.o pr_b.o
install:
	install -D $(TARGET) $(PREFIX)/$(TARGET)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)
