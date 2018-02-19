#include "scene.h"

// PMH
#include "assets_player.h"

// stl
#include <string.h>

/*
  GBA Constants
*/
// tile 8x8@4bpp: 32bytes; 8 ints
typedef struct {
  uint32_t data[8];
} TILE, TILE4;
// d-tile: double-sized tile (8bpp)
typedef struct {
  uint32_t data[16];
} TILE8;
// tile block: 32x16 tiles, 16x16 d-tiles
typedef TILE CHARBLOCK[512];
typedef TILE8 CHARBLOCK8[256];

#define tile_mem ((CHARBLOCK*)0x06000000)
#define tile8_mem ((CHARBLOCK8*)0x06000000)
#define sprite_palette_mem ((unsigned int*)0x05000200)
#define sprite_objects_mem ((SPRITE_OBJ*)0x07000000)

/*
  Scene class
*/
void Scene_init(Scene* self) {
  memset(&self->mSpriteObjectBuffer, 0, sizeof(self->mSpriteObjectBuffer));

  // Places the tiles of a 4bpp boxed metroid sprite
  //   into LOW obj memory (cbb == 4)
  memcpy(&tile_mem[4][0], assets_playerTiles, assets_playerTilesLen);
  memcpy(sprite_palette_mem, assets_playerPal, assets_playerPalLen);

  self->mSpriteAffineBuffer = (SPRITE_AFFINE*)self->mSpriteObjectBuffer;

  for (int i = 0; i < SPRITE_COUNT; ++i) {
    // Hide all sprites
    self->mSpriteObjectBuffer[i].mObjectMode = SPRITE_OBJ_OBJECT_MODE_HIDDEN;
  }

   // Initialize all sprites
  Scene_submit(self);
}

void Scene_submit(Scene* self) {
  // Copy Sprite objects into OAM
  for (int i = 0; i < SPRITE_COUNT; ++i) {
    sprite_objects_mem[i] = self->mSpriteObjectBuffer[i];
  }
}

void Scene_submit_one(Scene* self, int index) {
  sprite_objects_mem[index] = self->mSpriteObjectBuffer[index];
}