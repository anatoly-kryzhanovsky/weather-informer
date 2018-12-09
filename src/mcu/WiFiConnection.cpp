#include "ESP8266WiFi.h"
#include "WiFiConnection.h"

WifiConnection::WifiConnection(const char* ssid, const char* key, int connectionTimeout)
	:_ssid(ssid), _key(key), _logger(NULL), _connectionTimeout(connectionTimeout)
{
}

void WiFiConnection::setLogger(const Logger* logger)
{
	_logger = logger;
}

bool WiFiConnection::initialize()
{
	if(_logger)
		_logger->log("[WiFiConnection] Try to connect to network");
		 	
	WiFi.begin(_ssid, _key);
	
	int timeout = _connectionTimeout;
	while (WiFi.status() != WL_CONNECTED && timeout > 0) 
	{
    	delay(500);      
	  	timeout -= 500;
  	}
  
  	if(WiFi.status() != WL_CONNECTED && _logger)
		_logger->log("[WiFiConnection] Cannot connect to selected network");
  	else if(_logger)
  		_logger->log("[WiFiConnection] Connected to %s. IP address: %s", _ssid, WiFi.localIP());  	
}
	
bool WifiConnection::connect(const char* host, int port)
{
	_client.connect(host, port);
}

void WifiConnection::stop()
{
	_client.stop();
}
		
bool WifiConnection::connected()
{
	return _client.connected();
}

size_t WifiConnection::available()
{
	return _client.available();
}

size_t WifiConnection::read(char* buffer, size_t len)
{
	return _client.readBytes(buffer, len);
}
	
size_t WifiConnection::write(const char* buffer, size_t len)
{
	return _client.write(buffer, len);
}