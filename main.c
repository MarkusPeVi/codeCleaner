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
void sign_handler(int sig){
	switch(sig){
		case SIGINT :{ 
			printf("\nCaught a SIGINT-signal.\n Closing program...\n");
			writeToLog(log,"Caught a SIGINT-signal.\nnClosing program...\n");
			kill(0, SIGTERM);
			pid_t wPid;
			while((wPid = waitpid(-1, 0, WNOHANG)) != -1){
				if(wPid > 0){
				}
			}
			exit(0);
			     }
	}

}

int main(int argc, char* argv[]){
	signal(SIGINT, sign_handler);
	remove("cleanComments.log");
	log = open("cleanComments.log", O_RDWR | O_APPEND | O_CREAT| O_NONBLOCK);
	if(log < 0){
		perror("open");
		return -1;
	}
	writeToLog(log, "Starting to clean code(s)\n");	
		
	if(argc < 2){
		printf("To use this program you have to give atleast one file to clean, as an argument.\n");
		printf("For example:\n%s nameOfTheCodeToBeCleaned.c\n", argv[0]);
		
		writeToLog(log, "Stopping program because of too few arguments"); 	
		return -1;
	}

	for(int i = 1; i < argc; i++){
		pid_t pid = fork();
		if(pid == 0){
			char str[400];
			sprintf(str,"Starting to clean code from file %s\n", argv[i]);
			writeToLog(log, str);	 			
			char logStr[400];
			if(0 != cleanCode(argv[i], log)){
				printf("Failed to clean file %s\n", argv[i]);
				sprintf(logStr, "Failed to clean file %s\n", argv[i]);
				writeToLog(log, logStr);
			}else{
				sprintf(logStr, "Succesfully cleaned comments from file %s\n", argv[i]);
				writeToLog(log, logStr);
			}		
			exit(0);
		}	
	}
	// Check that all children have returned
	while(waitpid(-1, 0, WNOHANG) != -1){}
	return 0; 
}
