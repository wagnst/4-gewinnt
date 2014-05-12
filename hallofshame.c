#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void showHallOfShame(){
	FILE *fh;
	    char line[60];
	    char delimiter[] = ",";
	    char *partOfLine;
	    char victor[25];
	    char victim[25];
	    char moves[3];

	    fh = fopen("HallOfShame.txt", "r");

	    while((fscanf(fh,"%s",&line)) != EOF ) {

	    	// divide line into interessting parts
	        partOfLine = strtok(line, delimiter);
	        int i =0 ;
	        while(partOfLine != NULL) {

	        	switch (i%3) {
	         	case 0:
	         		strcpy(victor, partOfLine);
	         		break;
	         	case 1:
	         		strcpy(victim, partOfLine);
	         		break;
	         	case 2:
	         		strcpy(moves, partOfLine);
	         		break;
	         	default:
	         		break;
	         	}
	         	partOfLine = strtok(NULL, delimiter);
	         	i++;
	        }
	        printf("%s busted %s with %s moves\n",victor,victim,moves);
	    }
	    fclose(fh);
}

void updateSaveHoS(char* victor,char* victim,int moves){
	char line[60];
	FILE *fh;
	char* buffer = malloc((getOldFileLength()+strlen(victor)+strlen(victim))*sizeof(char)+3);
	if(buffer == NULL){
		printf("Allocation failed!");
	}
	buffer[0]='\0';


	int inserted =0;
	fh = fopen("HallOfShame.txt", "r");
	// while End-Of-File not reached line per line
	while((fscanf(fh,"%s",&line)) != EOF ) {
		printf("Line: %s \n",line);
		int currentMoves = extractMoves(line);
		if(currentMoves <= moves){
			strcat(line,"\n");
			strcat (buffer,line);
		}else{
			if(inserted==0){
				char insertLine[120];

				sprintf(insertLine,"%s,%s,%d\n%s\n",victor,victim,moves,line);
				strcat (buffer,insertLine);
				inserted = 1;
			}
			else{
				strcat(line,"\n");
				strcat (buffer,line);
			}
		}
	}
	printf("Buffer at the end: %s \n", buffer);
	char lastLine[60];
	if(inserted ==0){
		sprintf(lastLine,"%s,%s,%d\n",victor,victim,moves);
		strcat(buffer,lastLine);
	}
	fclose(fh);
	fh = fopen("HallOfShame.txt","w");
	fprintf(fh,buffer);
	fclose(fh);

}

int extractMoves(char* line){
	char work[60];
	strcpy(work,line);
	int moves =0;
	char *partOfLine;
	partOfLine = strtok(work, ",");
	int i =0 ;
	while(partOfLine != NULL) {
		switch (i%3) {
		case 2:
			moves = atoi(partOfLine);
			break;
		default:
			break;
		}
		partOfLine = strtok(NULL, ",");
		i++;
	}
	return moves;
}
int getOldFileLength()
{
    FILE *f = fopen("HallOfShame.txt", "rb");

    if (f == NULL || ferror(f))
    {
        if (f)
            fclose(f);
        return -1;
    }

    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    fclose(f);
    return len;
}
