#include <OLEDDisplayUi.h>
#include <SSD1306Wire.h>

#include "FCntp.h"
#include "mywifi.h"

SSD1306Wire display(0x3c, 5, 4);

OLEDDisplayUi ui(&display);

LoadingStage loadingStages[] = {
    {.process = "Conectando ao WiFi", .callback = []()
                                      { connectToWiFi(); }},
    {.process = "Conectado", .callback = []() {}},
    {.process = "Carregando dados do NTP",
     .callback = []()
     { getTimeFromNTP(); }},
};

int ntp_times = 0;
void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x,
                int16_t y)
{
  String hora = getFormattedTime();
  display->setFont(ArialMT_Plain_24);
  display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display->drawString(x + (128 / 2), y + (64 / 2), hora);
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x,
                int16_t y)
{
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 0, y + 0, "IP: " + WiFi.localIP().toString());
  display->drawString(x + 0, y + 10, "Hostname: " + String(WiFi.getHostname()));
  bool ntp_ok = updateNTP();
  display->drawString(x + 0, y + 20, "NTP OK: " + String(ntp_times));
  if (ntp_ok)
  {
    ntp_times += 1;
  }
}
FrameCallback frames[] = {drawFrame1, drawFrame2};

void setup()
{
  ui.init();
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.runLoadingProcess(loadingStages, 3);
  ui.setFrames(frames, 2);
}

void loop()
{
  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0)
  {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    delay(remainingTimeBudget);
  }
}