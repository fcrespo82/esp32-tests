#include "FCntp.h"

WiFiUDP udp;
NTPClient timeClient(udp, "a.st1.ntp.br", -3 * 3600); /* Cria um objeto "NTP" com as configurações.utilizada no Brasil */

void getTimeFromNTP()
{
    timeClient.begin();       /* Inicia o protocolo */
    timeClient.forceUpdate(); /* Atualização */

    while (!timeClient.isTimeSet())
    {
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
