#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
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

int writeToLog(int fp, char* str){
	time_t clock;
	time(&clock);
	struct tm *atTheMo = localtime(&clock);
	int h, min, sec, mon, day, year;
	char logInf[400];
	h = atTheMo->tm_hour;
	min = atTheMo -> tm_min;
	sec = atTheMo -> tm_sec;
	mon =atTheMo->tm_mon;		
	day = atTheMo-> tm_mday;
	year = atTheMo -> tm_year;
	// 	printf("%d.%d.%d %d:%d:%d\n", day,mon, 1900+ year, h, min, sec);
	sprintf(logInf, "%d.%d.%d %d:%d:%d ", day,mon, 1900+ year, h, min, sec);
	sprintf(logInf+strlen(logInf),"%s", str);
	int w;
	while( (w = write(fp, logInf, strlen(logInf))) == -1){
		if(w != EWOULDBLOCK &  w !=  EAGAIN){
			break;
		}	
	}
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
