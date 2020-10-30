#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int writeLogPid(char* str, int pid){
	FILE *fp;
	fp = fopen("cleanComments.log", "a");
	if(fp == NULL){
		printf("failed to open log-file\n");
		return -1;
	}
	int h, min, sec;
	time_t cloc;
	time(&cloc);
	struct tm *tim = localtime(&cloc);
	h = tim->tm_hour;
	min = tim->tm_min;
	sec = tim->tm_sec;
	fprintf(fp, "%02d:%02d:%02d: %s %d\n", h, min,sec, str, pid);	
	fclose(fp);
	return 0;

}
int writeLog(char* str, char*  arg){
	FILE *fp;
	fp = fopen("cleanComments.log", "a");
	if(fp==NULL){
		printf("Failed to open log-file\n");
	}
	int h, min, sec;
	time_t cloc;
	time(&cloc);
	struct tm *tim = localtime(&cloc);
	h = tim->tm_hour;
	min = tim->tm_min;
	sec = tim->tm_sec;
	fprintf(fp, "%02d:%02d:%02d: %s %s\n", h, min,sec, str, arg);	
	fclose(fp);
	return 0;
}

int newLog(char* str){
	FILE *fp;
	fp = fopen("cleanComments.log", "w");
	if(fp == NULL){
		printf("Failed to open logfile\n");
		
	}
	int h, min, sec;
	time_t cloc;
	time(&cloc);
	struct tm *tim = localtime(&cloc);
	h = tim->tm_hour;
	min = tim->tm_min;
	sec = tim->tm_sec;
	fprintf(fp, "%02d:%02d:%02d: %s \n", h, min,sec, str);	
	fclose(fp);
	return 0;
}
/*
int main(){
	char *haha1 = "haha xd lol";
	newLog(haha1);
	char *haha2 = "omg xs oot niin random";
	writeLog(haha2, "lol");
	return 0;
}
*/	
