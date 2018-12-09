#pragma once

#include "Arduino.h"

class Logger
{
private:
	char* _buffer;

public:	
	Logger();
	~Logger();
	
	void log(const char *s, ...);
};
