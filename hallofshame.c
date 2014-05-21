#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
* This function prints the HallOfShame.txt to the console.
*/
void showHallOfShame(){
	consoleClear();
	FILE *fh;
	char line[60];
	char delimiter[] = ",";
	char *partOfLine;
	char victor[20];
	char victim[20];
	char moves[3];
	line[0]='\0';
	fh = fopen("HallOfShame.txt", "r");
	output("\n\tWelcome to our Hall of Shame...\n");
	int somethingPrinted =0;
	while((fscanf(fh,"%59s",line)) != EOF ) {
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
		printf("\t\t%s busted %s with %s moves\n",victor,victim,moves);
		somethingPrinted =1;
	}
	fclose(fh);
	if(somethingPrinted == 0){
		printf("\t\tNo entries. Press any key to continue...");
	}
	getch();
}


/**
* This functions uses the 3 parameters to update and save the Hall of Shame.
* The 3 parameters will be interpreted as a line which has to be inserted to
* the HallOfShame.txt document. A kind of Insertion Sort is used to put the
* line on the right place.
* @param victor Name of player who won the game.
* @param vicitim Name of player who lost.
* @param moves Number of steps after the game has finished.
*/
void updateSaveHoS(char* victor,char* victim,int moves){
	char line[60];
	FILE *fh;
	char* buffer = malloc((getOldFileLength()+strlen(victor)+strlen(victim))*sizeof(char)+3);
	if(buffer == NULL){
		output("Allocation failed!");
	}
	buffer[0]='\0';


	int inserted =0;
	fh = fopen("HallOfShame.txt", "r");
	// while End-Of-File not reached line per line
	while((fscanf(fh,"%59s",line)) != EOF ) {

		int currentMoves = extractMoves(line);
		// compare both
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
	char lastLine[60];
	// this is the case when the new lines goes at the end
	if(inserted ==0){
		sprintf(lastLine,"%s,%s,%d\n",victor,victim,moves);
		strcat(buffer,lastLine);
	}
	//close the current file mode just for reading
	fclose(fh);
	//open file again in new mode, txt will be blank at the opening moment
	//so everything will be overwritten
	fh = fopen("HallOfShame.txt","w");
	fprintf(fh,buffer);
	fclose(fh);
	//do not forget to free your allocated memory
	free(buffer);

}

/**
* This function extracts the number of moves of the parameter line.
* @param line Pointer to char array (string).
* @return moves Just the moves as an int.
*/
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

/**
* Determine the length of the current HallOfShame.txt file.
* @return len Just the length of the HoS as an int.
*/
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
