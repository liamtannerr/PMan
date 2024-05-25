.PHONY: all
all: pman

pman: pman.c CommandHandler.c linkedlist.c
	gcc -Wall -o pman pman.c CommandHandler.c linkedlist.c

.PHONY: clean
clean:
	-rm -rf *.o pman

