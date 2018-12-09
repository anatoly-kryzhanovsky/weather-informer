#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Arduino.h"

class Logger
{
	public:
		void log(String *s);
    void log(char *s);
};

#endif
