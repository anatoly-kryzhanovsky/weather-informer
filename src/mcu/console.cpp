#include "console.h"

Console::Console(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display)
	: _display(display), _cursorX(0), _cursorY(0)
{
	_buffer = new char[(ScreenWidth + 1)* ScreenHeight];
}

void Console::scrollBuffer()
{
	for(int y = 0; y < ScreenHeight - 1; y++)
		memcpy(&_buffer[y * (ScreenWidth + 1)], &_buffer[(y + 1) * (ScreenWidth + 1)], ScreenWidth + 1);
}

void Console::writeLine(const char* s)
{
	write(s);
	write("\n");
}

void Console::write(const char* s)
{ 
	for(size_t i = 0; i < strlen(s); i++)
	{ 
		if(_cursorX == ScreenWidth || s[i] == '\n')
		{
			_buffer[_cursorY * (ScreenWidth + 1) + _cursorX] = 0;
			_cursorX = 0;

			if(_cursorY == ScreenHeight - 1)
				scrollBuffer();
			else     
				_cursorY++;
		}  
    
		if(s[i] != '\n')
		{
			_buffer[_cursorY * (ScreenWidth + 1) + _cursorX] = s[i];
			_cursorX++;
		}		
	}
  
	_buffer[_cursorY * (ScreenWidth + 1) + _cursorX] = 0; 
	showBuffer();    
}

void Console::clear()
{
	_cursorX = 0;
	_cursorY = 0;
	
	for(int i = 0; i < ScreenHeight; i++)		
		_buffer[i] = 0;
	
	showBuffer();
}

void Console::showBuffer()
{
	_display->setFont(u8g2_font_5x8_t_cyrillic);
	_display->clearBuffer();

	for(int i = 0; i < ScreenHeight; i++)
		_display->drawUTF8(0, (i + 1) * LineHeight, &_buffer[i * (ScreenWidth + 1)]); 
      
	_display->sendBuffer();
}