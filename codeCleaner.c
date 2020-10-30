#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "log.h"

void sig_handler(int sig){
	//printf("\nCaught SIGINT-signal.\nExiting program...\n");
	// write to log-file
	printf("SIGINT caught at codeCleaner\n");
	//	writeLog("Caught SIGINT-signal,", "exiting program...");
	exit(0);// closes files and frees used memory 	

}
void sig_term_hand(int sig){
	printf("Caught SIGTERM-signal\n");
	exit(0);

}


int cleanCode(char* filNam){
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_term_hand);
	FILE *fp, *fp2;
	fp = fopen(filNam, "r"); //opens the given file and checks it has gone without failures.
	if(fp == NULL){
		printf("Failed to open given file: %s \n", filNam);
		writeLog("Failed to open given file:", filNam);
		return -1;	
	
	}
	
	//char* destFil = malloc(strlen(filNam)*sizeof(char));
	//strcat(destFil, filNam);
	//destFil = realloc(destFil, strlen(destFil)*sizeof(char)+ strlen(".clean"));
	//strcat(destFil, ".clean");	
	size_t length = strlen(filNam) + strlen(".clean") +1;
	char *destFil = (char*) malloc(sizeof(char)*length);
	snprintf(destFil, length, "%s%s", filNam, ".clean");
	fp2 = fopen(destFil, "w");
	free(destFil);
	if(fp2==NULL){
		printf("Failed to create file for cleaned code\n");
		writeLog("Failed to create file for cleaned code to file:", filNam);
		return -1;
	}
	int c; // when reading file the basic char, pointer location on file
	int c2; // if there is a possibility that c is a begining of a comment next char from file
	int comline = 0; // marks if current line is a oneline comment
	int multicom = 0; // if we are in the middle of a comment
	int newLine =0;  // marker for a new line
	int dist = 0; // amount of chars after newline
	int atEnd =0; // marks if there is a need for a new line after the comment ends
	int atString =0;
	while(1){
		c = fgetc(fp);
		if(c != '\t'){
			dist++;	
		}	
		if(feof(fp)){
			break;
		}

		if(c== '\n'){
			newLine = 1;
			dist =0;	
		}
		if(dist > 1){
			newLine = 0;
		}
		if(c == '"' && multicom == 0 && comline==0){
			if(atString ==0) atString = 1;
			else atString =0;
		}	

		if(c == '/' && atString ==0){
			c2 = fgetc(fp);
			if(c2 == '/'){
				comline = 1;
				if(newLine != 1){
				 atEnd = 1;
				}
			}
			else if(c2 == '*'){
				multicom = 1;	
				if(newLine != 1){
				 atEnd = 1;
				}
			}else{
				fputc(c, fp2);
				c = c2;
			}
		}

		if(multicom == 1 || comline == 1){
			if(c == '\n'){
				comline =0;
				if(atEnd == 1){
					fputc('\n', fp2);
//					printf("\n");
				}
				atEnd =0;
			}else if(c == '*'){
			 	c2 = fgetc(fp);
				if(c2 == '/'){
					multicom =0;
					if(atEnd == 1){
					fputc('\n', fp2);
//					printf("\n");
					}
					atEnd= 0;
				}
			}
		}else{
			fputc(c, fp2);
//			printf("%c", c);

		}
	}
	
	fclose(fp);
	fclose(fp2);
	return 0;
}


/*
int main(int argc, char* argv[]){
	cleanCode("testCode.c");
	return 0;
}
*/