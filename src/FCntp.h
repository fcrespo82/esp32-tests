#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include <NTPClient.h>   /* https://github.com/arduino-libraries/NTPClient */
#include <WiFi.h>        /* Biblioteca do WiFi. */

void getTimeFromNTP(OLEDDisplay *display);
bool updateNTP();

String getFormattedTime();