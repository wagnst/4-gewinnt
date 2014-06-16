#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
* This function prints a certain number (c.f. HOS_LINES) of lines of
* the HallOfShame.dat to the console.
* @param highlight Highlight a special line with "-> "
* @param startFrom The output is reduced to a constant number of lines
* 		 (c.f. variables.h HOS_LINES). The parameter controls
*		 which lines actually are printed.
*/
void showHallOfShame(int highlight,int startFrom){
	int viewHoS = 1;
	// correct the argument if necessary
	startFrom = startFrom > 0 ? startFrom : 0;
	while(viewHoS){
			//decalartions
		startBuffer(64);
		FILE *fh;
		char victor[20];
		char victim[20];
		char moves[4];
		//counting the lines
		int lineCounter = 0;
		//open file in read mode
		//or leave loop
		fh = fopen("HallOfShame.dat", "r");
		if (fh == NULL || ferror(fh)){
			if (fh){
				fclose(fh);
				break;
			}
		}

		setLineAlign(0);
		output("[ HALL OF SHAME ]\n\nWelcome to our Hall of Shame...\n");
		setLineAlign(-1);
		// notice if HoS is empty
		int somethingPrinted =0;
		while((fscanf(fh,"%19[^,],%19[^,],%2[^,^\n]",victor,victim,moves)) != EOF ) {

			while (victor[0] == '\n'){
				memmove(victor, victor+1, strlen(victor));
			}
			if(lineCounter>=startFrom && lineCounter<=startFrom+HOS_LINES && strlen(victor)>0 && strlen(victim)>0){
				if(highlight==lineCounter){
				output("-->%d. %s busted %s with %s moves\n",lineCounter+1,victor,victim,moves);
				somethingPrinted =1;
				}
				else{
				output(" %d.   %s busted %s with %s moves\n",lineCounter+1,victor,victim,moves);
				somethingPrinted =1;
				}
			}

			lineCounter++;
		}
		fclose(fh);
		if(somethingPrinted == 0){
			output("   No entries.");
		}
		output("\n");
		setLineAlign(0);
		output("[...Press up/down for scrolling...]\n");
		output("[...Press  Enter/Escape to exit...]\n");
		flushBuffer();
		fflush(stdin);
		char userInput = getch();
		switch(userInput) {
				case 72:    // key up
					startFrom = startFrom-1 > 0 ? startFrom-1 : 0;
					break;
				case 80:    // key down
					startFrom = startFrom+1 < lineCounter-HOS_LINES ? startFrom+1 : startFrom;
					break;

				case 13: // key enter
					viewHoS=0;
				break;
				case 27: //escape
					viewHoS =0;
				//default:
				//	viewHoS=0;
		}
		fflush(stdin);
	}
}


/**
* This functions uses the 3 parameters to update and save the Hall of Shame.
* The 3 parameters will be interpreted as a line which has to be inserted to
* the HallOfShame.dat document. A kind of Insertion Sort is used to put the
* line on the right place.
* @param victor Name of player who won the game.
* @param vicitim Name of player who lost.
* @param moves Number of steps after the game has finished.
* @return The line number of the inserted one.
*/
int updateSaveHoS(char* victor,char* victim,int moves){
	char line[60];
	FILE *fh;
	char* buffer = malloc((getOldFileLength()+strlen(victor)+strlen(victim))*sizeof(char)+3);
	int insertedLineNumber = 0;
	if(buffer == NULL){
		exit(EXITCODE_OUTOFMEMORY);
	}
	buffer[0]='\0';


	int inserted =0;
	fh = fopen("HallOfShame.dat", "r");
	// while End-Of-File not reached line per line
	while((fscanf(fh,"%59[^\n]\n",line)) != EOF ) {

		int currentMoves = extractMoves(line);
		// compare both
		if(currentMoves <= moves){
			strcat(line,"\n");
			strcat (buffer,line);
			insertedLineNumber++;
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
	//open file again in new mode, dat will be blank at the opening moment
	//so everything will be overwritten
	fh = fopen("HallOfShame.dat","w");
	fprintf(fh,buffer);
	fclose(fh);
	//do not forget to free your allocated memory
	free(buffer);
	return insertedLineNumber;
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
* Determine the length of the current HallOfShame.dat file.
* @return len Just the length of the HoS as an int.
*/
int getOldFileLength()
{
    FILE *f = fopen("HallOfShame.dat", "rb");

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
