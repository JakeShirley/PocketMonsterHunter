#pragma once

// stl
#include <stdint.h>

// PocketMonsterHunter
#include "sprite.h"

#define SPRITE_COUNT 128
typedef struct Scene {
    SPRITE_OBJ mSpriteObjectBuffer[SPRITE_COUNT];
    SPRITE_AFFINE *mSpriteAffineBuffer;
} Scene;

void Scene_init(Scene* self);
void Scene_submit(Scene* self);
void Scene_submit_one(Scene* self, int index);