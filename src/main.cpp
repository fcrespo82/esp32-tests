#include <NTPClient.h>   /* https://github.com/arduino-libraries/NTPClient */
#include <WiFi.h>        /* Biblioteca do WiFi. */
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`

#include "images.h"

/*-------- Configurações de Wi-fi----------- */
const char *ssid = "HouseCrespo";      // iPhone de Fernando"; /* Substitua pelo nome da rede */
const char *password = "Maia11Joao14"; /* Substitua pela senha */
/* -------- Configurações de relógio on-line----------- */
WiFiUDP udp;
NTPClient timeClient(udp, "a.st1.ntp.br", -3 * 3600); /* Cria um objeto "NTP" com as configurações.utilizada no Brasil */
String hora;                                          /* Variável que armazena */
SSD1306Wire display(0x3c, 5, 4);                      // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h

WiFiServer server(80);

int percent = 0;
void setup()
{
  Serial.begin(115200);

  display.init();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawStringMaxWidth(0, 0, 127, "Conectando ao Wifi... " + String(ssid));
    display.drawProgressBar(0, 63 / 2, 127, 10, (percent++ % 101));
    display.display();
    delay(10);
  }
  display.clear();
  display.drawStringMaxWidth(0, 0, 127, "Conectado ao Wi-Fi " + WiFi.localIP().toString());
  display.display();
  delay(200);

  timeClient.begin();       /* Inicia o protocolo */
  timeClient.forceUpdate(); /* Atualização */

  while (!timeClient.isTimeSet())
  {
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawStringMaxWidth(0, 0, 127, "Lendo dados do servidor NTP");
    display.drawProgressBar(0, 63 / 2, 127, 10, (percent++ % 101));
    display.display();
    delay(10);
  }
  server.begin(); // start the web server on port 80
}

void wificlient()
{
  WiFiClient client = server.available(); // listen for incoming clients

  if (client)
  {                               // if you get a client,
    Serial.println("new client"); // print a message out the serial port
    String currentLine = "";      // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        if (c == '\n')
        { // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:

            client.println("Hora: " + hora + "<br/>");
            client.println("IP: " + WiFi.localIP().toString() + "<br/>");
            client.println("Hostname: " + String(WiFi.getHostname()) + "<br/>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else
          { // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H"))
        {
          digitalWrite(27, HIGH); // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(27, LOW); // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void loop()
{
  wificlient();
  /* Armazena na variável hora, o horário atual. */
  hora = timeClient.getFormattedTime();
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Hora: " + hora);
  display.drawString(0, 10, "IP: " + WiFi.localIP().toString());
  display.drawString(0, 20, "Hostname: " + String(WiFi.getHostname()));
  display.display(); /* Exibe o display. */
  timeClient.update();
  delay(100);
}
