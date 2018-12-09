#ifndef __STATION_H__
#define __STATION_H__

#include "RestClient.h"
#include "ArduinoJson.h"
#include "Arduino.h"
#include "U8g2lib.h"
#include "Time.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "console.h"
#include "logger.h"

class Station 
{
	private:
		const char* SSID = "Exception";
		const char* Password = "gfhjkmegshm";
		const int NTP_PACKET_SIZE = 48;		
    const unsigned int localPort = 8888;
    const int timeZone = 4;
		static IPAddress NtpServer;
		
		const int HTTP_OK = 200;
		const int CITY_ID = 472757;
		const int CURRENT =    0;
		const int FORECAST_3 = 1;
		const int FORECAST_6 = 2;
		const char* APP_KEY = "95da1d8c5ac24ebf561c0a6382ce9f9b";
		
	private:
		U8G2_SSD1306_128X64_NONAME_F_HW_I2C* _display;
		Console* _console;
		byte* _packetBuffer;
		RestClient* _restClient;
		Logger* _logger;
    WiFiUDP _udp;
    	
	private:
		void syncTime();
		time_t getTime();
		void sendNTPRequest();
		
		void getCurrentWeather();
		void getForecastWeather();
		void displayWeather(int line, int iconId, int temperature, float windSpeed, float windDirection);
		String getWindDirectionname(float windDirection);
		unsigned char* getWeatherIcon(int weatherId);

   Station(Logger* logger, Console* console, U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display);

  public:
    static void begin(Logger* logger, Console* console, U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display);
    static Station* Instance;
    static time_t syncProvider();
		
	public:
		void initialize();
		void display();
   
};

#endif
