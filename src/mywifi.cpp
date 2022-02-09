#include "mywifi.h"

/*-------- Configurações de Wi-fi----------- */
const char *ssid = "HouseCrespo";      // iPhone de Fernando"; /* Substitua pelo nome da rede */
const char *password = "Maia11Joao14"; /* Substitua pela senha */

void connectToWiFi()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
    }
}