#pragma once

#include "WiFiClient.h"
#include "connection.h"
#include "logger.h"

class WifiConnection: public Connection
{
	private:
		WiFiClient _client;
		const char* _ssid;
		const char* _key;
		const Logger* _logger;
		int _connectionTimeout;		
	
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
