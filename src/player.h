#pragma once

// PMH
#include "point.h"

// stl
#include <stdbool.h>
#include <stdint.h>

typedef struct InputHandler InputHandler;
typedef struct SPRITE_OBJ SPRITE_OBJ;

typedef struct Player {
// public
Point mPosition;

// private
const InputHandler* _mInputHandler;
SPRITE_OBJ* _mSprite;
uint32_t _mWalkFrame;
bool _mAltWalkFrame;
} Player;

// Methods
void Player_init(Player* self, const InputHandler* inputHandler,
                 SPRITE_OBJ* sprite);

void Player_update(Player* self);