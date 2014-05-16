#pragma once
#include <stdio.h>
#include <stdarg.h>

int output(const char* input, ...)
{
	//printing everything directly, buffer implementation will follow
	int result;
	va_list args;
	va_start(args, input);
	result = vprintf(input, args);
	va_end(args);
	return result;
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
