#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "codeCleaner.h"
#include "log.h"

static int log;

int main(int argc,char* argv[]){
	log = open("cleanComments.log", O_RDWR | O_APPEND | O_CREAT| O_NONBLOCK);
	if(log < 0){
		perror("open");
		return -1;
	}
	if(argc < 2){
		printf("To use this program you have to give atleast one file to clean, as an argument.\n");
		printf("For example:\n%s nameOfTheCodeToBeCleaned.c\n", argv[0]);
		
		writeToLog(log, "Stopping program because of too few arguments"); 	
		return -1;
	}
	char str[400];
	sprintf(str,"Starting to clean code from file %s\n", argv[1]);
	writeToLog(log, str);	 			
	char logStr[400];
	if(0 != cleanCode(argv[1], log)){
		printf("Failed to clean file %s\n", argv[1]);
		sprintf(logStr, "Failed to clean file %s\n", argv[1]);
		writeToLog(log, logStr);
	}else{
		sprintf(logStr, "Succesfully cleaned comments from file %s\n", argv[1]);
		writeToLog(log, logStr);
		printf("succes\n");
	}
	return 0;
}
