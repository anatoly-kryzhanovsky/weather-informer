#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "U8g2lib.h"

class Console 
{
	private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C* _display;
		const char** _buffer;
		int _x;
		int _y;
	
	public:
		Console(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display);

    void writeLine(const char* s);
		void writeLine(String* s);

    void write(const char* s);
		void write(String* s);	
    
		void clear();
};

#endif
