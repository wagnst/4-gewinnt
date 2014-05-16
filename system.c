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
