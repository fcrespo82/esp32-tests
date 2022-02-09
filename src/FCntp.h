#include <NTPClient.h>   /* https://github.com/arduino-libraries/NTPClient */
#include <WiFi.h>        /* Biblioteca do WiFi. */

void getTimeFromNTP();
bool updateNTP();

String getFormattedTime();