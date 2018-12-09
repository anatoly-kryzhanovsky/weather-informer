#pragma once

#include "U8g2lib.h"

class Console 
{
private:
	const int ScreenWidth = 25;
	const int ScreenHeight = 7;
	const int LineHeight = 10;
	
private:
	U8G2_SSD1306_128X64_NONAME_F_HW_I2C* _display;
	char* _buffer;
	int _cursorX;
	int _cursorY;	
	
public:
	Console(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display);

	void writeLine(const char* s);
	void write(const char* s);	
    
	void clear();
	
private:
	void scrollBuffer();
	void showBuffer();
};