#include "player.h"

// PMH
#include "input.h"
#include "sprite.h"

#define PLAYER_FRAME_DIR_DOWN 0
#define PLAYER_FRAME_DIR_LEFT 2
#define PLAYER_FRAME_DIR_RIGHT 4
#define PLAYER_FRAME_DIR_UP 6
#define PLAYER_FRAME_TILE_OFFSET 16
#define PLAYER_WALK_FRAME_INTERVAL 10

void Player_init(Player* self, const InputHandler* inputHandler,
                 SPRITE_OBJ* sprite) {
  self->_mInputHandler = inputHandler;
  self->mPosition = (Point){0, 0};

  self->_mWalkFrame = 0;
  self->_mAltWalkFrame = false;

  // Set up sprite
  self->_mSprite = sprite;
  sprite->mX = self->mPosition.x;
  sprite->mY = self->mPosition.y;
  sprite->mSpriteShape = 0;  // Square
  sprite->mSpriteSize = 2;   // 32x32
  sprite->mPalleteBankIndex = 0;
  sprite->mTileIndex = 0;
  sprite->mObjectMode = SPRITE_OBJ_OBJECT_MODE_NORMAL;
}

void Player_update(Player* self) {
  bool moved = false;

  uint32_t facingDirection = 0;

  if (InputHandler_IsKeyPressed(self->_mInputHandler, INPUT_KEY_LEFT)) {
    self->mPosition.x--;
    moved = true;
    facingDirection = PLAYER_FRAME_DIR_LEFT;
  } else if (InputHandler_IsKeyPressed(self->_mInputHandler, INPUT_KEY_RIGHT)) {
    self->mPosition.x++;
    moved = true;
    facingDirection = PLAYER_FRAME_DIR_RIGHT;
  } else if (InputHandler_IsKeyPressed(self->_mInputHandler, INPUT_KEY_UP)) {
    self->mPosition.y--;
    moved = true;
    facingDirection = PLAYER_FRAME_DIR_UP;
  } else if (InputHandler_IsKeyPressed(self->_mInputHandler, INPUT_KEY_DOWN)) {
    self->mPosition.y++;
    moved = true;
    facingDirection = PLAYER_FRAME_DIR_DOWN;
  }

  if (moved) {
    self->_mWalkFrame++;
    if (self->_mWalkFrame % PLAYER_WALK_FRAME_INTERVAL == 0) {
      self->_mAltWalkFrame = !self->_mAltWalkFrame;
    }

    // Update Sprite
    self->_mSprite->mX = self->mPosition.x & 0x00FF;
    self->_mSprite->mY = self->mPosition.y & 0x00FF;

    self->_mSprite->mTileIndex =
        (facingDirection + (self->_mAltWalkFrame ? 1 : 0)) *
        PLAYER_FRAME_TILE_OFFSET;
  }
}