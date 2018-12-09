#pragma once

class Connection 
{
public:
	virtual bool initialize();
	virtual void setLogger(const Logger* logger);
	
	virtual bool connect(const char* host, int port) = 0;
	virtual void stop() = 0;
		
	virtual bool connected() = 0;
	virtual size_t available() = 0;
				
	virtual size_t read(char* buffer, size_t len) = 0;
	virtual size_t write(const char* buffer, size_t len) = 0;
};
