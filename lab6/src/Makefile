PREFIX = /usr/local/bin
CC = clang
LIBS =  -lrt -lpthread
.PHONY: all clean install uninstall

all: shmemsemclient shmemsemserver
clean:
	rm -rf shmemsem{client,server} *.o
shmemsemserver.o: server.c
	$(CC)  -c -o shmemsemserver.o server.c $(LIBS)
shmemsemclient.o: client.c
	$(CC)  -c -o shmemsemclient.o client.c $(LIBS)
shmemsemclient: shmemsemclient.o
	$(CC)  -o shmemsemclient shmemsemclient.o $(LIBS)
shmemsemserver: shmemsemserver.o
	$(CC)  -o shmemsemserver shmemsemserver.o $(LIBS)
install:
	install -D shmemsemserver $(PREFIX)/shmemsemserver
	install -D shmemsemclient $(PREFIX)/shmemsemclient
uninstall:
	rm -rf $(PREFIX)/shmemsem{client,server}
