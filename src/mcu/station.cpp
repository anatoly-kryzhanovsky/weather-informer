#include "station.h"
#include <TimeLib.h> 
#include "icons.h"

IPAddress Station::NtpServer(88, 147, 254, 232);
Station* Station::Instance = NULL;

void Station::begin(Logger* logger, Console* console, U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display)
{
  Instance = new Station(logger, console, display);  
}

time_t Station::syncProvider()
{
  return Instance->getTime();
}

Station::Station(Logger* logger, Console* console, U8G2_SSD1306_128X64_NONAME_F_HW_I2C* display)
	: _display(display), _console(console), _logger(logger)
{
  _display->setFont(u8g2_font_9x15_t_cyrillic);  
	_packetBuffer = new byte[NTP_PACKET_SIZE];	
}

void Station::syncTime()
{
  _logger->log("[syncTime] start");
  _logger->log("[syncTime] connecting to network");
	_console->writeLine("Connecting to network...");
	WiFi.begin(SSID, Password);
  
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);    
	}
  _logger->log((String("[syncTime] connected to network ") + String(SSID)).c_str());
  
	_udp.begin(localPort);

  setSyncProvider(Station::syncProvider);
  
	_console->writeLine((String("Connected to network ") + String(SSID)).c_str());

  _logger->log("[syncTime] wait time synchronization");
	_console->writeLine("Wait NTP time...");  
	while(timeStatus() != timeSet)
		delay(250);

  _logger->log("[syncTime] time setted");
	WiFi.disconnect();

  time_t dt = now();
  _logger->log((String("dt ") + String(hour(dt)) + ":" + String(minute(dt)) + String(":") + String(second(dt))).c_str());
  _logger->log("[syncTime] finish");
}

time_t Station::getTime()
{
  _logger->log("[getTime] start");
  _logger->log("[getTime] flush data in channel");
  while (_udp.parsePacket() > 0);

  _logger->log("[getTime] request time");
  sendNTPRequest();
  uint32_t beginWait = millis();

  _logger->log("[getTime] wait data");
  while (millis() - beginWait < 2500) 
  {
    int size = _udp.parsePacket();
    _logger->log((String("[getTime] received packet ") + String(size)).c_str());
    if (size >= NTP_PACKET_SIZE) 
	  {
      _udp.read(_packetBuffer, NTP_PACKET_SIZE); 
      unsigned long secsSince1900;
      secsSince1900 =  (unsigned long)_packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)_packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)_packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)_packetBuffer[43];

      _logger->log("[getTime] received responce");
      _logger->log("[getTime] finish");
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }

  _logger->log("[getTime] can't get responce (timeout)");
  _logger->log("[getTime] finish");
  return 0;
}

void Station::sendNTPRequest()
{
  _logger->log("[sendNTPRequest] start");
  
  memset(_packetBuffer, 0, NTP_PACKET_SIZE);
  _packetBuffer[0] = 0b11100011;
  _packetBuffer[1] = 0;
  _packetBuffer[2] = 6;
  _packetBuffer[3] = 0xEC;
  
  _packetBuffer[12]  = 49;
  _packetBuffer[13]  = 0x4E;
  _packetBuffer[14]  = 49;
  _packetBuffer[15]  = 52;

  _logger->log("[sendNTPRequest] send data");
  _udp.beginPacket(NtpServer, 123);
  _udp.write(_packetBuffer, NTP_PACKET_SIZE);
  _udp.endPacket();

  _logger->log("[sendNTPRequest] finish");
}

void Station::initialize()
{
  _logger->log("[initialize] start");
	_display->begin();
	_display->enableUTF8Print();	 

  _logger->log("[initialize] sync time");
	_console->writeLine("Synchronize time...");
	syncTime();
	_console->writeLine("Time synchronized");

  _logger->log("[initialize] setup rest client");
	_console->writeLine("Initialize rest client...");
	_console->writeLine("Connect to WiFi");   
	_restClient = new RestClient("api.openweathermap.org");
	_restClient->begin("Exception", "gfhjkmegshm");
	_console->writeLine("Connection to WiFi established");  
	_console->writeLine("System ready"); 	

  _logger->log("[initialize] finish");
  
	delay(5000);
}

void Station::getCurrentWeather() 
{  
  _logger->log("[getCurrentWeathertialize] start");
  String response = "";
  int statusCode = _restClient->get((String("/data/2.5/weather?id=") + String(CITY_ID) + String("&appid=") + String(APP_KEY)).c_str(), &response);

  _logger->log((String("[getCurrentWeathertialize] request executed ") + String(statusCode)).c_str());
  if(statusCode != HTTP_OK) {
    _logger->log("Cannot execute request /data/2.5/weather. Response code: " + String(statusCode));    
    _logger->log("[getCurrentWeathertialize] finish");
    return;
  }

  DynamicJsonDocument doc;
  deserializeJson(doc, response);

  JsonObject root = doc.as<JsonObject>();
  JsonObject weather = root["weather"];
  JsonObject main = root["main"];
  JsonObject wind = root["wind"];
  
  int weatherId = weather["icon"].as<int>();
  int temperature = main["temp"].as<int>();
  float windSpeed = wind["speed"].as<float>();
  float windDirection = wind["deg"].as<float>();
    
  displayWeather(CURRENT, weatherId, temperature, windSpeed, windDirection);
  _logger->log((String("Current weather: ") + String(weatherId) + String(", ") + String(temperature) + String(", ") + String(windSpeed) + String(", ") + String(windDirection)).c_str());
  _logger->log("[getCurrentWeathertialize] finish");
}

void Station::getForecastWeather() 
{
  _logger->log("[getForecastWeatherntWeathertialize] start");
  String response = "";
  int statusCode = _restClient->get((String("/data/2.5/forecast?id=") + String(CITY_ID) + String("&appid=") + String(APP_KEY) + String("&cnt=3")).c_str(), &response);

  _logger->log((String("[getForecastWeatherntWeathertialize] response length ") + String(response.length())).c_str());
  _logger->log((String("[getForecastWeatherntWeathertialize] request executed ") + String(statusCode)).c_str());
  if(statusCode != HTTP_OK) {
    _logger->log(("Cannot execute request /data/2.5/forecast. Response code: " + String(statusCode)).c_str());
    _logger->log("[getForecastWeatherntWeathertialize] finish");
    return;
  }

  DynamicJsonDocument doc;
  deserializeJson(doc, response);

  _logger->log(String(response));

  JsonObject root = doc.as<JsonObject>();
  JsonArray list = root["list"];

  {
    JsonObject itm3 = list[0];    
    JsonObject main = itm3["main"];
    JsonObject weather = itm3["weather"];
    JsonObject wind = itm3["wind"];
    time_t dt = itm3["dt"].as<time_t>();
  
    int weatherId = weather["icon"].as<int>();
    int temperature = main["temp"].as<int>();
    float windSpeed = wind["speed"].as<float>();
    float windDirection = wind["deg"].as<float>();

    _logger->log((String("dt ") + String(hour(dt)) + ":" + String(minute(dt)) + String(":") + String(second(dt))).c_str());
    _logger->log((String("Forecast3: ") + String(weatherId) + String(", ") + String(temperature) + String(", ") + String(windSpeed) + String(", ") + String(windDirection)).c_str());
    displayWeather(FORECAST_3, weatherId, temperature, windSpeed, windDirection);
  }

  {
    JsonObject itm6 = list[1];
    JsonObject main = itm6["main"];
    JsonObject weather = itm6["weather"];
    JsonObject wind = itm6["wind"];
  
    int weatherId = weather["icon"].as<int>();
    int temperature = main["temp"].as<int>();
    float windSpeed = wind["speed"].as<float>();
    float windDirection = wind["deg"].as<float>();

    _logger->log((String("Forecast6: ") + String(weatherId) + String(", ") + String(temperature) + String(", ") + String(windSpeed) + String(", ") + String(windDirection)).c_str());
    displayWeather(FORECAST_6, weatherId, temperature, windSpeed, windDirection);
  }

  _logger->log("[getForecastWeatherntWeathertialize] finish");
}

void Station::displayWeather(int line, int iconId, int temperature, float windSpeed, float windDirection) {
  _display->setFont(u8g2_font_9x15_t_cyrillic);  
  _logger->log("[displayWeather] start");
    
  String temperatureStr = String(String(temperature > 273 ? "+" : "") + String(temperature - 273) + "C");  
  _display->drawUTF8(24, (line + 1) * 4 + line * 16 + 12, temperatureStr.c_str());

  _display->setFont(u8g2_font_5x8_t_cyrillic);
  _display->drawUTF8(5 * 9 + 18, (line + 1) * 4 + line * 16 + 5, String(String(windSpeed)+ " " + "м/с").c_str());  
  _display->drawUTF8(5 * 9 + 18, (line + 1) * 4 + line * 16 + 15, String(getWindDirectionname(windDirection)).c_str());     

  _display->drawXBM(4, (line + 1) * 4 + line * 16, 16, 16, getWeatherIcon(iconId));

  _logger->log("[displayWeather] finish");
}


String Station::getWindDirectionname(float windDirection) {
  _logger->log("[getWindDirectionname] start");
  
  if(windDirection > 22.5 && windDirection <= 67.5)
    return "СЗ";

  if(windDirection > 67.5 && windDirection <= 112.5)
    return "З";

  if(windDirection > 112.5 && windDirection <= 157.5)
    return "ЮЗ";

  if(windDirection > 157.5 && windDirection <= 202.5)
    return "Ю";

  if(windDirection > 202.5 && windDirection <= 247.5)
    return "ЮВ";

  if(windDirection > 247.5 && windDirection <= 292.5)
    return "В";

  if(windDirection > 292.5 && windDirection <= 337.5)
    return "СВ";

  return "С";

  _logger->log("[getWindDirectionname] finish");
}

unsigned char* Station::getWeatherIcon(int weatherId) 
{
  _logger->log("[getWeatherIcon] start");
  
  if(weatherId == 800)
    return IconSun;

  if(weatherId == 801)
    return IconCloudLight;

  if(weatherId == 802)
    return IconCloud;

  if(weatherId == 803 || weatherId == 804)
    return IconCloudHeavy;

  _logger->log("[getWeatherIcon] finish");
  return IconSun;
}

void Station::display()
{  
	//if(minutes % 60 == 0) 
	{
		_display->clearBuffer();
		getCurrentWeather();
		getForecastWeather();
		_display->sendBuffer();
	}
}
