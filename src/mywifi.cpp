#include "mywifi.h"

/*-------- Configurações de Wi-fi----------- */
const char *ssid = "HouseCrespo";      // iPhone de Fernando"; /* Substitua pelo nome da rede */
const char *password = "Maia11Joao14"; /* Substitua pela senha */

void connectToWiFi(OLEDDisplay *display)
{
    int percent = 0;
    display->clear();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        display->clear();
        display->setFont(ArialMT_Plain_10);
        display->drawStringMaxWidth(0, 0, 127, "Conectando ao Wifi... " + String(ssid));
        display->drawProgressBar(0, 63 / 2, 127, 10, (percent++ % 101));
        display->display();
    }
    display->clear();
    display->drawStringMaxWidth(0, 0, 127, "Conectado ao Wi-Fi " + WiFi.localIP().toString());
    display->display();
}