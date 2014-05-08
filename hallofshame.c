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
//	    return 0;
}

void updateSaveHoS(char* victor,char* victim,int moves){
	char line[60];
	FILE *fh;
	char* buffer = malloc( (getOldFileLength()+strlen(victor)+strlen(victim)+3)*sizeof(char));
	int inserted =0;
	fh = fopen("HallOfShame1.txt", "r");
	while((fscanf(fh,"%s",&line)) != EOF ) {
		printf("Line: %s \n",line);
		int currentMoves = extractMoves(line);
		if(currentMoves <= moves){
			strcat (buffer,line);
		}else{
			if(inserted==0){
				sprintf(buffer,"%s,%s,%s\n%s",victor,victim,moves,line);
//				strcat (buffer,line);
				inserted = 1;
			}
			else{
				strcat (buffer,line);
			}
		}
		printf("%s\n",buffer);
	}
	if(inserted ==0){
		sprintf(buffer,"%s,%s,%d\n",victor,victim,moves);
	}
	fclose(fh);
	fh = fopen("HallOfShame1.txt","w");
	fprintf(fh,buffer);
	fclose(fh);

}

int extractMoves(char* line){
	int moves =0;
	char *partOfLine;
	partOfLine = strtok(line, ",");
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
