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
	//signal handler for SIGINT signals
	printf("\nCaught a SIGINT-signal.\n Closing program...\n");
	char exitEntry[500];
	sprintf(exitEntry," PID:%d :Caught a SIGINT-signal.Closing program...\n", getpid()); 
	writeToLog(log, exitEntry);
	// Sends SIGTERM-signal so all processes are closed properly
	kill(0, SIGTERM);
	pid_t wPid;
	while((wPid = waitpid(-1, 0, WNOHANG)) != -1){
		if(wPid > 0){
			//kills notresponding child processes
			kill(wPid, SIGKILL);	
		}

	}
	// Closes everything involved in this process gracefully
	exit(0);

}

int main(int argc, char* argv[]){
	signal(SIGINT, sign_handler);
	//defines SIGINT -signal handler
	remove("cleanComments.log");
	//Opens file with right to be accessed by multiple users with rights to read, write, append and create file etc
	log = open("cleanComments.log", O_RDWR | O_APPEND | O_CREAT| O_NONBLOCK, 0777);
	if(log < 0){
		perror("open");
		return -1;
	}
	writeToLog(log, "Starting to clean code(s)\n");	
	//calls writeLog function	
	if(argc < 2){
		printf("To use this program you have to give atleast one file to clean, as an argument.\n");
		printf("For example:\n%s nameOfTheCodeToBeCleaned.c\n", argv[0]);
		writeToLog(log, "Stopping program because of too few arguments"); 	
		return -1;
	}

	for(int i = 1; i < argc; i++){
		pid_t pid = fork();
		if(pid == 0){
			// exec command that calls ./cleaner binary which handles cleaning a codefile.
			execl("./cleaner", ".",argv[i], NULL );
			exit(0);
		}	
	}
	// Check that all children have returned
	while(waitpid(-1, 0, WNOHANG) != -1){}
	close(log);
	return 0; 
}
