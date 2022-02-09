#include "FCntp.h"

WiFiUDP udp;
NTPClient timeClient(udp, "a.st1.ntp.br", -3 * 3600); /* Cria um objeto "NTP" com as configurações.utilizada no Brasil */

void getTimeFromNTP(OLEDDisplay *display)
{
    int percent = 0;
    timeClient.begin();       /* Inicia o protocolo */
    timeClient.forceUpdate(); /* Atualização */

    while (!timeClient.isTimeSet())
    {
        display->clear();
        display->setFont(ArialMT_Plain_10);
        display->drawStringMaxWidth(0, 0, 127, "Lendo dados do servidor NTP");
        display->drawProgressBar(0, 63 / 2, 127, 10, (percent++ % 101));
        display->display();
    }
}

bool updateNTP()
{
    return timeClient.update();
}

String getFormattedTime()
{
    return timeClient.getFormattedTime();
}
