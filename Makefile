CC = gcc
CFLAGS = -Wall -pedantic -g  



cleanCode: main.o codeCleaner.o log.o 
	$(CC) -o cleanCode $(CFLAGS) main.o codeCleaner.o log.o



main.o: main.c codeCleaner.o log.o
	$(CC) -c $(CFLAGS)  main.c

codeCleaner.o: codeCleaner.c codeCleaner.h
	$(CC) -c $(CFLAGS) codeCleaner.c


log.o: log.c log.h
	$(CC) -c $(CFLAGS) log.c

cleanAll: cleanO
	rm -rf *.clean *.log
	make cleanO
cleanO:
	rm -rf *.o
