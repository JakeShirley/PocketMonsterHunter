#include <math.h>
#include <stdint.h>
#include <stdlib.h>

static const uint16_t RED = 0x001F;    // 000000000011111 Red
static const uint16_t GREEN = 0x03E0;  // 000001111100000 Green
static const uint16_t BLUE = 0x7C00;   // 111110000000000 Blue
static const uint16_t BLACK = 0x0;     // Black
static const uint16_t WHITE = 0xFFFF;  // Black

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define CURSOR_HISTORY_COUNT 20
#define CURSOR_SCALE 100

static uint16_t *const SCREEN = ((uint16_t *)0x06000000);

#include "assets/tileset_biome.c"
#include "input.h"

static uint16_t *const TIMERS[4] = {
    ((uint16_t *)0x4000100), ((uint16_t *)0x4000104), ((uint16_t *)0x4000108),
    ((uint16_t *)0x400010C)};
static uint16_t *const TIMER_CONTROLS[4] = {
    ((uint16_t *)0x4000102), ((uint16_t *)0x4000106), ((uint16_t *)0x400010A),
    ((uint16_t *)0x400010E)};

typedef struct Point {
  int x;
  int y;
} Point;

void setPixel(Point pt, uint16_t color) { SCREEN[pt.x + pt.y * 240] = color; }

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

int mod(int a, int b) {
  int r = a % b;
  return r < 0 ? r + b : r;
}

void updateSnake(const InputHandler *inputHandler) {
  static Point cursorPoints[CURSOR_HISTORY_COUNT] = {0};
  static int cursorIndex = 0;

  static Point cursorPos = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

  bool moved = false;
  if (InputHandler_IsKeyPressed(inputHandler, INPUT_KEY_LEFT)) {
    cursorPos.x--;
    moved |= (cursorPos.x % CURSOR_SCALE == 0);
  }
  if (InputHandler_IsKeyPressed(inputHandler, INPUT_KEY_RIGHT)) {
    cursorPos.x++;
    moved |= (cursorPos.x % CURSOR_SCALE == 0);
  }
  if (InputHandler_IsKeyPressed(inputHandler, INPUT_KEY_UP)) {
    cursorPos.y--;
    moved |= (cursorPos.y % CURSOR_SCALE == 0);
  }
  if (InputHandler_IsKeyPressed(inputHandler, INPUT_KEY_DOWN)) {
    cursorPos.y++;
    moved |= (cursorPos.y % CURSOR_SCALE == 0);
  }

  if (moved) {
    Point pixel = cursorPos;
    pixel.x /= CURSOR_SCALE;
    pixel.y /= CURSOR_SCALE;

    pixel.x = mod(pixel.x, SCREEN_WIDTH);
    pixel.y = mod(pixel.y, SCREEN_HEIGHT);

    // Set last pixel
    setPixel(cursorPoints[cursorIndex], RED);

    // Set current pixel
    cursorIndex = (cursorIndex + 1) % CURSOR_HISTORY_COUNT;

    cursorPoints[cursorIndex] = pixel;
    setPixel(cursorPoints[cursorIndex], GREEN);

    // Clear tail pixel
    setPixel(cursorPoints[(cursorIndex + 1) % CURSOR_HISTORY_COUNT], BLACK);
  }
}

int main() {
  InputHandler inputHandler;
  InputHandler_init(&inputHandler);

  setupTimer();

  *(uint16_t *)0x04000000 = 0x0403;  // 10000000011, video mode

  uint16_t oldTimerValues[4] = {0, 0, 0, 0};

  while (1) {
    InputHandler_update(&inputHandler);

    updateSnake(&inputHandler);

    setPixel((Point){120, 96}, BLUE);

    for (int i = 0; i < 1; ++i) {
      const int xOff = (240 / (i + 1)) + 15;
      if (*TIMERS[i] % 1000 == 0) {
        setPixel((Point){xOff, oldTimerValues[i]}, BLACK);
        oldTimerValues[i]++;
        oldTimerValues[i] = oldTimerValues[i] % 160;
        setPixel((Point){xOff, oldTimerValues[i]}, WHITE);
      }
    }
  }

  return 0;
}
