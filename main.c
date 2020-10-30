#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "codeCleaner.h"
#include "log.h"
void sign_handler(int sig){
	switch(sig){
		case SIGINT :{ 
			printf("\nCaught a SIGINT-signal.\n Closing program...\n");
			writeLog("Caught a SIGINT-signal.","Closing program...\n");
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
	
	if(argc < 2){
		printf("To use this program you have to give atleast one file to clean, as an argument.\n");
		printf("For example:\n%s nameOfTheCodeToBeCleaned.c\n", argv[0]);
		
		newLog("Stopping program because of too few arguments"); 	
		return -1;
	}
	newLog("Starting to clean code(s)");	

	for(int i = 1; i < argc; i++){
		pid_t pid = fork();
		if(pid == 0){
			sleep(20);
			writeLog("Starting to clean code from file ", argv[i]);
			if(0 != cleanCode(argv[i])){
				printf("Failed to clean file %s\n", argv[i]);
				writeLog("Failed to clean comments from file", argv[i]);
			}else{
				
				writeLog("Succesfully cleaned comments from file", argv[i]);
			}		
			exit(0);
		}	
	}
	// Check that all children have returned
	while(waitpid(-1, 0, WNOHANG) != -1){}
	return 0; 
}
