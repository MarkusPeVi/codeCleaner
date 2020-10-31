CC = gcc
CFLAGS = -Wall -pedantic   


cleanCode: main.o codeCleaner.o log.o  
	$(CC) -o cleanCode $(CFLAGS) main.o codeCleaner.o log.o
	make exec
exec:  cleanCode.c codeCleaner.o log.o
	$(CC)  -o cleaner $(CFLAGS) cleanCode.c codeCleaner.o log.o
	

main.o: main.c codeCleaner.o log.o
	$(CC) -c $(CFLAGS)  main.c

codeCleaner.o: codeCleaner.c codeCleaner.h
	$(CC) -c $(CFLAGS) codeCleaner.c


log.o: log.c log.h
	$(CC) -c $(CFLAGS) log.c

cleanAll: cleanO
	rm -rf *.clean *.log *.dSYM  
	make cleanO
	make cleanBinary
cleanO:
	rm -rf *.o
cleanBinary:
	rm cleaner
	rm cleanCode

