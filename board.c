#pragma once
//Board-Core: Create board, read&update field, draw board
#include <string.h>

struct board myBoard;

/**
* Creates new clean and usable board (including memory allocation)
* Warning: To resize an existing board call freeBoard() before to prevent memory leak
* @param target Pointer to a fresh board structure.
* @param width Board width (>=4).
* @param height Board height (>=4).
*/
int newBoard(struct board* target, unsigned int width, unsigned int height)
{
	//sanity check
	if (width<4 || height<4) {
		return 0;
	}

	//Initialize board
	target->width = width;
	target->height = height;
	target->numberOfFields = width*height;
	target->content = malloc(target->numberOfFields * sizeof(char) + 1);

	//abort if memory allocation failed
	if (target->content == NULL) {
		return 0;
	}

	//board is ready, now clear it
	clearBoard(target);

	return 1;
}

/**
* Removes all chips from the board
* @param target Already existing board.
*/
void clearBoard(struct board* target) {
	//fills the whole board with space chars
	int i;
	for (i = 0; i < target->numberOfFields; i++) {
		*((target->content) + i) = FIELD_EMPTY;
	}
	//add null terminator which allows direct board content debug output
	*(target->content + i) = '\0';
}

/**
* Internal helper method to calculate the data offset of a given field on the board
* @param target Board to base calculations on.
* @param x X-coordinate.
* @param y Y-coordinate.
*/
char* calcFieldAddress(struct board* target, int x, int y) {
	int offset = y*(target->width) + x;
	return (target->content + offset);
}

/**
* Gets what is on a given field of the board (see FIELD_XYZ constants)
* @param target Board to read.
* @param x X-coordinate.
* @param y Y-coordinate.
*/
char getField(struct board* target, int x, int y) {
	return *calcFieldAddress(target, x, y);
}

/**
* Sets what is on a given field of the board (see FIELD_XYZ constants)
* @param target Board to change.
* @param x X-coordinate.
* @param y Y-coordinate.
* @param value Field value (FIELD_EMPTY/FIELD_PLAYER1/FIELD_PLAYER2).
*/
void setField(struct board* target, int x, int y, char value) {
	*calcFieldAddress(target, x, y) = value;
}

/**
* Frees memory taken by a board (warning: makes it unusable until newBoard() has been called again)
* @param target Board to free memory.
*/
void freeBoard(struct board* target) {
	free(target->content);
}

/**
* Outputs a graphical representation of the given board to the console
* @param target Board to draw.
*/
void drawBoard(struct board* target) {
	//calculate dimensions of output and reserve memory
	char* canvas;

	//4 chars wide per field plus ending bar and newline
	int charsWidth  = target->width*4 + 2;
	//4 chars wide per field plus stand
	int charsHeight = target->height*2 + 3;
	//multiply by 6 for full UTF-8 eventualities plus 1 for string terminator \0
	int totalSize = charsWidth*charsHeight*6 + 1;

	canvas = malloc(totalSize * sizeof(char));

	if (canvas==NULL) {
		output("Memory allocation for graphics failed.");
		return;
	}

	//writing-to-canvas setup
	canvas[0] = '\0';

	int fieldX;
	int fieldY;

	//loop over rows and build 2 console lines (grid + values) per loop
	for(fieldY = target->height - 1; fieldY >= 0; fieldY--) {

		//grid row
		for(fieldX = 0; fieldX < target->width; fieldX++) {
			if (fieldY == target->height - 1 && fieldX == 0) {
				strcat(canvas,"/");
			} else if (fieldY == target->height - 1) {
				strcat(canvas,"~");
			} else if (fieldX == 0) {
				strcat(canvas,"(");
			} else {
				strcat(canvas,"+");
			}
			strcat(canvas,"---");
		}

		//end of grid row
		if (fieldY == target->height - 1) {
			strcat(canvas,"\\");
		} else {
			strcat(canvas,")");
		}
		strcat(canvas,"\n");

		//value row
		for(fieldX = 0; fieldX < target->width; fieldX++) {
			strcat(canvas,"| ");
			char field = getField(target,fieldX,fieldY);
			if (field==FIELD_EMPTY)   strcat(canvas," ");
			if (field==FIELD_PLAYER1) strcat(canvas,"X");
			if (field==FIELD_PLAYER2) strcat(canvas,"O");
			strcat(canvas," ");
		}

		//finish value row
		strcat(canvas,"|\n");

	}

	//build stand
	for(fieldX = 0; fieldX < target->width; fieldX++) {
		if (fieldX == 0) {
			strcat(canvas,"(---");
		} else {
			strcat(canvas,"~---");
		}
	}
	strcat(canvas,")\n");
	for(fieldX = 0; fieldX < target->width; fieldX++) {
		if (fieldX == 0) {
			strcat(canvas,"\\---");
		} else {
			strcat(canvas,"----");
		}
	}
	strcat(canvas,"/\n");

	//we're done, output the whole thing
	output("%s",canvas);
}
