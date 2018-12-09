#include "U8g2lib.h"

#include "console.h"
#include "station.h"
#include "logger.h"

Logger logger;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);
Console console(&display);

void setup() {
  Serial.begin(9600);
  
  Station::begin(&logger, &console, &display);
  Station::Instance->initialize();
}

void loop() {  
  Station::Instance->display();
  
  delay(60 * 1000);
  //minutes++;
}
