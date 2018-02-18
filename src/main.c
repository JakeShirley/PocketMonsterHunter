#include <math.h>
#include <stdint.h>
#include <stdlib.h>

static const uint16_t RED = 0x001F;    // 000000000011111 Red
static const uint16_t GREED = 0x03E0;  // 000001111100000 Green
static const uint16_t BLUE = 0x7C00;   // 111110000000000 Blue
static const uint16_t BLACK = 0x0;     // Black
static const uint16_t WHITE = 0xFFFF;  // Black

static uint16_t *const SCREEN = ((uint16_t *)0x06000000);

#include "assets/tileset_biome.c"

static uint16_t *const TIMERS[4] = {
    ((uint16_t *)0x4000100), 
    ((uint16_t *)0x4000104), 
    ((uint16_t *)0x4000108),
    ((uint16_t *)0x400010C)};
static uint16_t *const TIMER_CONTROLS[4] = {
    ((uint16_t *)0x4000102), 
    ((uint16_t *)0x4000106), 
    ((uint16_t *)0x400010A),
    ((uint16_t *)0x400010E)};

void setPixel(int x, int y, uint16_t color) { SCREEN[x + y * 240] = color; }

void setupTimer() {
/*
Bit   Expl.
0-1   Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
2     Count-up Timing   (0=Normal, 1=See below)  ;Not used in TM0CNT_H
3-5   Not used
6     Timer IRQ Enable  (0=Disable, 1=IRQ on Timer overflow)
7     Timer Start/Stop  (0=Stop, 1=Operate)
8-15  Not used
*/

  *TIMER_CONTROLS[0] = 0b0000000010000011;  // Enabled with F/1024 speed
  //*TIMER_CONTROLS[1] = 0b0000000010000010; // Enabled with F/256 speed
  //*TIMER_CONTROLS[2] = 0b0000000010000001; // Enabled with F/64 speed
  //*TIMER_CONTROLS[3] = 0b0000000010000000; // Enabled with F/1 speed
}

int main() {
  setupTimer();

  *(uint16_t *)0x04000000 = 0x0403;  // 10000000011, video mode

  uint16_t oldTimerValues[4] = {0, 0, 0, 0};

  while (1) {
    setPixel(120, 80, (uint16_t)rand());
    setPixel(120, 96, BLUE);

    for (int i = 0; i < 1; ++i) {
      const int xOff = (240 / (i + 1)) + 15;
      if (*TIMERS[i] % 1000 == 0) {
        setPixel(xOff, oldTimerValues[i], BLACK);
        oldTimerValues[i]++;
        oldTimerValues[i] = oldTimerValues[i] % 160;
        setPixel(xOff, oldTimerValues[i], WHITE);
      }
    }
  }

  return 0;
}
