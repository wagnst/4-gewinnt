#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

struct OutBuffer display;
CONSOLE_SCREEN_BUFFER_INFO csbi;
int consoleBufferWidth = 80;
int consoleBufferHeight = 15;

/**
* Initializes buffering
* Warning: Only call once at program start
*/
void initBuffer(){
	//set text size maximum and insert a first empty line
	display.first = NULL;
	display.last = NULL;
	display.lineCount = 0;
}

/**
* Add a new line to the buffer, may be inserted in the middle or appended to the end
* Warning: Use output() to add text, this method is only used internally
* @param prev Pointer to the previous line struct, NULL appends line to start of buffer.
* @param next Pointer to the next line struct, NULL if this is the last element (most used case).
* @param align Text align for the new line, -1 is left aligned, 0 is centered, +1 is right aligned.
* @param maxTextLength Maximum number of characters for this line.
* @return Pointer to new created struct.
*/
struct LineItem* insertNewLineItem(struct LineItem* prev, struct LineItem* next, int align, int maxTextLength){

	//allocate memory for line item
	struct LineItem* newLine = malloc(sizeof(struct LineItem));
	if (newLine==NULL){
		exit(EXITCODE_OUTOFMEMORY);
	}

	//allocate memory for text
	newLine->text = malloc(maxTextLength * sizeof(char) * UTF_MULTIPLIER + 1);
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
	if (line==NULL){
		return;
	}

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
* Copy one character (UTF8-aware) from the source string to the target string and append a null byte afterwards
* @param src Source string pointer.
* @param dst Destination string pointer.
* @return Returns how many bytes were copied
*/
int copyChar(char* src, char* dst){

	//determine the length of the string, see http://en.wikipedia.org/wiki/UTF-8#Description
	int bytes = 0;
	char slider = *src;
	while ((slider & 0x80) == 0x80){
		slider<<=1;
		bytes++;
	}
	bytes+=!bytes;

	//copy <bytes>-byte long character
	int cursor = 0;
	int length = bytes;
	while (length--){
		dst[cursor] = src[cursor];
		cursor++;
	}

	//append null byte and return length of copied data
    dst[cursor] = '\0';
    return bytes;
}

/**
* Add text to output buffer, use EXACTLY like printf()
* @param input Format string, see printf().
* @param ... Parameters, see printf().
* @return Return value of internal vsnprintf().
*/
int output(const char* input, ...){
	if (display.first==NULL || display.last==NULL){
        exit(EXITCODE_BUFFERERROR);
	}

	int result;
	va_list args;
	va_start(args, input);
#ifdef DEBUG
	printf("[DEBUGPRINT:]");
	result = vprintf(input, args);
#endif
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
			current->length++;
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
	if (display.first==NULL || display.last==NULL){
        exit(EXITCODE_BUFFERERROR);
	}

	if(GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi)) {
		consoleBufferWidth = csbi.dwSize.X;
		consoleBufferHeight = csbi.dwSize.Y;
	}

	consoleClear();


	/*### DEBUGGING START ###*/
#ifdef DEBUG
	consoleClear();

	static int flushed = 0;
	printf("DEBUG: printing %d-line buffer (%d.)",display.lineCount,++flushed);
	struct LineItem* debugchain = display.first;
	printf(", chain: %d",(int)debugchain);
	do {
		printf("(%d)->%d",debugchain->length,(int)debugchain->next);
		debugchain = debugchain->next;
	} while (debugchain!=NULL);
	printf(". [END:%d]\n--------------------------------------------------\n",(int)display.last);
#endif // DEBUG
	/*### DEBUGGING END ###*/

	struct LineItem* current = display.first;
	const int MAX_CHARS_BORDER = 4;
	const int MAX_BYTES_PER_LINE = (display.maxTextLength + MAX_CHARS_BORDER + 1) * sizeof(char) * UTF_MULTIPLIER;
	char* collector = malloc(display.lineCount * MAX_BYTES_PER_LINE + 1);
	if (collector==NULL){
		exit(EXITCODE_OUTOFMEMORY);
	}
	collector[0] = '\0';
	int i;

	//draw header line
	strcat(collector," ");
	strcat(collector,FONT_DPIPE_TOP_LEFT);
	for (i = 0; i < display.maxTextLength; i++){
		strcat(collector,FONT_DPIPE_HORI_BAR);
	}
	strcat(collector,FONT_DPIPE_TOP_RIGHT);
	strcat(collector," ");
	strcat(collector,"\n");

	//temporary:
	printf("%s",collector);
	collector[0] = '\0';

	//draw lines
	while (current!=NULL){
		//left border
		strcat(collector," ");
		strcat(collector,FONT_DPIPE_VERT_BAR);
		//text
		strcat(collector,current->text);
		//right padding and right border
		for (i = 0; i < display.maxTextLength - current->length; i++){
			strcat(collector," ");
		}
		strcat(collector,FONT_DPIPE_VERT_BAR);
		strcat(collector," ");
		strcat(collector,"\n");
		current = current->next;
		//temporary:
		printf("%s",collector);
		collector[0] = '\0';
	}
	//draw footer line
	strcat(collector," ");
	strcat(collector,FONT_DPIPE_BOTTOM_LEFT);
	for (i = 0; i < display.maxTextLength; i++){
		strcat(collector,FONT_DPIPE_HORI_BAR);
	}
	strcat(collector,FONT_DPIPE_BOTTOM_RIGHT);
	strcat(collector," ");

	printf("%s",collector);
	collector[0] = '\0';

	free(collector);

	deleteLineItem(display.first, 1);
	initBuffer();
}

/**
* Starts a new screen and sets line limit, empties the buffer
* @param maxTextLength See initBuffer().
*/
void startBuffer(int maxTextLength){
	if (display.first!=NULL || display.last!=NULL){
        exit(EXITCODE_BUFFERERROR);
	}

	display.maxTextLength = maxTextLength;
	deleteLineItem(display.first, 1);
	display.lineCount = 0;
	display.first = insertNewLineItem(NULL,NULL,-1,maxTextLength);
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
/**
* convert string to upper string
* @param ch1 string to be uppered
* @return ch2 is upper case char
*/
char lower_to_upper(char ch1)
{
      char ch2;

      if(ch1 >= 'a' && ch1 <= 'z'){
            ch2 = ('A' + ch1 - 'a');
            return ch2;
      }
      else{
            ch2 = ch1;
            return ch2;
      }
}

void strcatRepeat(char* target, const char* source, unsigned int howOften){
	int c;
	for(c = 0; c < howOften; c++){
		strcat(target,source);
	}
}
