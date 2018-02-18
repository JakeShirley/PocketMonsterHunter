#include "input.h"

static uint16_t* const REG_KEYPINPUT = (uint16_t*)0x4000130;

void InputHandler_init(InputHandler* self) {
  self->_mCurrentKeystates = 0;
  self->_mPreviousKeystates = 0;
}

void InputHandler_update(InputHandler* self) {
  self->_mPreviousKeystates = self->_mCurrentKeystates;
  self->_mCurrentKeystates = *REG_KEYPINPUT;
}

bool InputHandler_IsKeyPressed(const InputHandler* self, INPUT_KEY key) {
  return (~self->_mCurrentKeystates & (uint32_t)key);
}

bool InputHandler_IsKeyTriggered(const InputHandler* self, INPUT_KEY key) {
  return (~self->_mCurrentKeystates & self->_mPreviousKeystates) & (uint32_t)key;
}

bool InputHandler_IsKeyHeld(const InputHandler* self, INPUT_KEY key) {
  return (~self->_mCurrentKeystates & ~self->_mPreviousKeystates) & (uint32_t)key;
}

bool InputHandler_IsKeyReleased(const InputHandler* self, INPUT_KEY key) {
  return (self->_mCurrentKeystates & ~self->_mPreviousKeystates) & (uint32_t)key;
}