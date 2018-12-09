#include "logger.h"

Logger::Logger()
{
    _buffer = new char[512];
}

Logger::~Logger()
{
    delete[] _buffer;
}

void Logger::log(const char* s, ...)
{
    va_list args;
    va_start(args, s);
    vsprintf(_buffer, s, args);
    va_end(args);
  
    Serial.println(_buffer);
}
