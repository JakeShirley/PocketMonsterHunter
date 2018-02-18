#pragma once

#include <stdint.h>
#include <stdbool.h>

// A crude attempt at strongly typed enums
typedef struct INPUT_KEY { uint32_t _empty[1]; } *INPUT_KEY; // we use 'empty' so that we don't get a warning that empty structs are a GNU extension

#define INPUT_KEY_A ((INPUT_KEY)        (1 << 0))
#define INPUT_KEY_B ((INPUT_KEY)        (1 << 1))
#define INPUT_KEY_SELECT ((INPUT_KEY)   (1 << 2))
#define INPUT_KEY_START ((INPUT_KEY)    (1 << 3))
#define INPUT_KEY_RIGHT ((INPUT_KEY)    (1 << 4))
#define INPUT_KEY_LEFT ((INPUT_KEY)     (1 << 5))
#define INPUT_KEY_UP ((INPUT_KEY)       (1 << 6))
#define INPUT_KEY_DOWN ((INPUT_KEY)     (1 << 7))
#define INPUT_KEY_R ((INPUT_KEY)        (1 << 8))
#define INPUT_KEY_L ((INPUT_KEY)        (1 << 9))

typedef struct InputHandler {
  uint32_t _mCurrentKeystates;
  uint32_t _mPreviousKeystates;
} InputHandler;

void InputHandler_init(InputHandler* self);
void InputHandler_update(InputHandler* self);

bool InputHandler_IsKeyPressed(const InputHandler* self, INPUT_KEY key);
bool InputHandler_IsKeyTriggered(const InputHandler* self, INPUT_KEY key);
bool InputHandler_IsKeyHeld(const InputHandler* self, INPUT_KEY key);
bool InputHandler_IsKeyReleased(const InputHandler* self, INPUT_KEY key);