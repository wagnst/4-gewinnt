#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

struct OutBuffer display;

/**
* Initializes buffering
* Warning: Only call once at program start
* @param maxTextLength Maximum character length of every single line, auto-wrap occurs after this number is reached.
*/
void initBuffer(int maxTextLength){
	//set text size maximum and insert a first empty line
	display.maxTextLength = maxTextLength;
	display.lineCount = 0;
	display.first = insertNewLineItem(NULL,NULL,-1,maxTextLength);
}

/**
* Add a new line to the buffer, may be inserted in the middle or appended to the end
* Warning: Use output() to add text, this method is only used internally
* @param prev Pointer to the previous line struct, NULL appends line to start of buffer.
* @param next Pointer to the next line struct, NULL if this is the last element (most used case).
* @param align Text align for the new line, -1 is left aligned, 0 is centered, +1 is right aligned.
* @param maxTextLength Maximum number of characters for this line.
*/
struct LineItem* insertNewLineItem(struct LineItem* prev, struct LineItem* next, int align, int maxTextLength){

	//allocate memory for line item
	struct LineItem* newLine = malloc(sizeof(struct LineItem));
	if (newLine==NULL){
		exit(EXITCODE_OUTOFMEMORY);
	}

	//allocate memory for text
	newLine->text = malloc(maxTextLength * sizeof(char) * 6 + 1);
	if (newLine->text==NULL){
		exit(EXITCODE_OUTOFMEMORY);
	}
	newLine->text[0] = '\0';

	//set line properties
	newLine->align = align;
	newLine->byteSize = 0;
	newLine->length = 0;

	//relink previous item if given
	newLine->prev = prev;
	if (prev!=NULL){
		newLine->prev->next = newLine;
	}

	//chain to next item if given
	newLine->next = next;
	if (newLine->next!=NULL){
        newLine->next->prev = newLine;
	}

	//update buffer's first&last pointers
	if (prev==NULL){
		//display.first = newLine;
	}
	if (next==NULL){
		display.last = newLine;
	}

	//update line count and return created line
	display.lineCount++;
	return newLine;
}

/**
* Delete the given line from the buffer
* @param line Pointer to the line struct to delete.
* @param deleteAllBelow Delete all the following lines as well (1) or just the given line (0).
*/
void deleteLineItem(struct LineItem* line, int deleteAllBelow){
	if (!deleteAllBelow){
		//fix the chain by connecting the following line to the previous
		if (line->prev!=NULL){
			line->prev->next = line->next;
		}
	} else {
		//recursive delete requested
		if (line->next!=NULL){
			deleteLineItem(line->next,1);
		}
		if (line->prev!=NULL){
			line->prev->next = NULL;
		}
	}
	free(line->text);
	free(line);
	display.lineCount--;
}

/**
* Copy one character from the source string to the target string and append a null byte afterwards
* Warning/TODO: Not yet UTF8 aware!
* @param src Source string pointer.
* @param dst Destination string pointer.
*/
int copyChar(char* src, char* dst){
    *dst = *src;
    *(dst+1) = '\0';
    return 1;
}

/**
* Add text to output buffer, use EXACTLY like printf()
* @param input Format string, see printf().
* @param ... Parameters, see printf().
*/
int output(const char* input, ...){
	int result;
	va_list args;
	va_start(args, input);
	//TODO: add buffer handling everywhere and remove direct print
	result = vprintf(input, args);
	va_end(args);

	//writing to string buffer
	char buffer[OUTPUT_MAXBUFFER+1];
	buffer[0] = '\0';
	result = vsnprintf(buffer, OUTPUT_MAXBUFFER+1, input, args);

	//keep track of string buffer position and the current line to write to
	int i = 0;
	struct LineItem* current = display.last;

	//loop through buffer and copy to lines
	while(buffer[i]!='\0'){
		if (current->length < display.maxTextLength && buffer[i]!='\n'){
			//line not full yet, copy char
			int increase = copyChar(buffer+i, current->text+current->byteSize);
			i += increase;
			current->byteSize += increase;
			//TODO: UTF8 aware:
			current->length = strlen(current->text);
		} else {
			//end line in input: start new line
			if (buffer[i]=='\n'){
				i++;
			}
			//end line or line full, create new one
			current->next = insertNewLineItem(current->prev, NULL, -1, display.maxTextLength);
			current = current->next;
		}
	}

	return result;
}

/**
* Prints the screen (output buffer) and clears the buffer
*/
void flushBuffer(){
	consoleClear();
	static int flushed = 0;

	/*### DEBUGGING START ###*/
	printf("DEBUG: printing %d-line buffer (%d.)",display.lineCount,++flushed);
	struct LineItem* debugchain = display.first;
	printf(", chain: %d",(int)debugchain);
	do {
		printf("(%d)->%d",debugchain->length,(int)debugchain->next);
		debugchain = debugchain->next;
	} while (debugchain!=NULL);
	printf(". [END:%d]\n--------------------------------------------------\n",(int)display.last);
	/*### DEBUGGING END ###*/


	struct LineItem* current = display.first;
	while (current!=NULL){
		printf("%s\n",current->text);
		current = current->next;
	}

	startBuffer();
}

/**
* Starts a new screen, empties the buffer
*/
void startBuffer(){
	deleteLineItem(display.first, 1);
	initBuffer(display.maxTextLength);
}

/**
* Clears the console
*/
void consoleClear(){
	//should clear the console on most plattforms
	#ifdef _WIN32
	//detected windows System (both 32 and 64bit)-->use windows clear
		system("CLS");
	#else
	//detected other (non windows) System-->unse Unix-clear
		system("clear");
	#endif

}
