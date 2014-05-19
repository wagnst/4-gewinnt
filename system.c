#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

struct OutBuffer display;

void initBuffer(int maxTextLength){
	//set text size maximum and insert a first empty line
	display.maxTextLength = maxTextLength;
	display.lineCount = 0;
	display.first = insertNewLineItem(NULL,NULL,-1,300);
}

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

int copyChar(char* src, char* dst){
	//TODO: UTF8 handling!
    *dst = *src;
    *(dst+1) = '\0';
    return 1;
}

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
	snprintf(buffer, OUTPUT_MAXBUFFER+1, input, args);

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

	emptyBuffer();
}

void emptyBuffer(){
	deleteLineItem(display.first, 1);
	initBuffer(display.maxTextLength);
}

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
