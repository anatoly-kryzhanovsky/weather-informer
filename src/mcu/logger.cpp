#include "logger.h"

void Logger::log(String* s)
{
	Serial.println(*s);
}

void Logger::log(char* s)
{
  Serial.println(s);
}
