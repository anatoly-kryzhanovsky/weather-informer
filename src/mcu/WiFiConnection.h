#ifndef __WIFICONNECTION_H__
#define __WIFICONNECTION_H__

#include "connection.h"

class WifiConnection: public Connection
{
	private:
		WiFiClient _client;
		const char* _ssid;
		const char* _key;
		const Logger* _logger;
		int _connectionTimout;
		char* _buffer;		
	
	public: 
		WifiConnection(const char* ssid, const char* key, int connectionTimeout);
		
		virtual bool initialize();
		virtual void setLogger(const Logger* logger);
	
		virtual bool connect(const char* host, int port);
		virtual void stop();
		
		virtual bool connected();
		virtual size_t available();
		
		virtual size_t read(char* buffer, size_t len);
		virtual size_t write(const char* buffer, size_t len);
};

#endif