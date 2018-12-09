#include "console.h"

Console::Console(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display)
	: _display(display), _x(0), _y(0)
{
	_buffer = new const char*[8];
}

void Console::writeLine(const char* s)
{
  _display->setFont(u8g2_font_5x8_t_cyrillic);  
  _x = 0;
  _buffer[_y] = s;
  
  _display->clearBuffer();

  bool scrollNeeded = _y == 7;
  for(int i = 0; i < _y; i++)
      _display->drawUTF8(0, i * 10, _buffer[i + (scrollNeeded ? 1 : 0)]);

  if(!scrollNeeded)
    _y++;
    
  _display->sendBuffer();
}

void Console::writeLine(String* s)
{
  writeLine(s->c_str());
}

void Console::write(const char* s)
{
   _display->setFont(u8g2_font_5x8_t_cyrillic);  
  
  if(!_buffer[_y])
    _buffer[_y] = s;
  //else
    //_buffer[_y] += *s;  
  
  _display->clearBuffer();  
  _display->drawUTF8(_x, _y * 10, _buffer[_y]);   
  _display->sendBuffer();
  
  _x += strlen(_buffer[_y]) * 5;  
}

void Console::write(String* s)
{
  write(s->c_str());
}

void Console::clear()
{
	_y = 0;
	_x = 0;
	
	for(int i = 0; i < 8; i++)
		if(_buffer[i])
      _buffer[i] = "";
	
	_display->clearBuffer();	
	_display->sendBuffer();
}
