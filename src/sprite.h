#pragma once

// stl
#include <stdint.h>

#define SPRITE_OBJ_OBJECT_MODE_NORMAL         0
#define SPRITE_OBJ_OBJECT_MODE_AFFINE         1
#define SPRITE_OBJ_OBJECT_MODE_HIDDEN         2
#define SPRITE_OBJ_OBJECT_MODE_AFFINE_DOUBLE  3

#define SPRITE_OBJ_GRAPHICS_MODE_NORMAL       0
#define SPRITE_OBJ_GRAPHICS_MODE_ALPHA        1
#define SPRITE_OBJ_GRAPHICS_MODE_WINDOW_MASK  2

#define SPRITE_OBJ_COLOR_MODE_4BPP            0
#define SPRITE_OBJ_COLOR_MODE_8BPP            1

// TODO: Add forced word alignment '__attribute__((aligned(4)))'
typedef struct SPRITE_OBJ {
  /*
      Attribute 0
  */
  uint32_t mY : 8;           // Marks top of sprite
  uint32_t mObjectMode : 2;  // 00 = Normal, 01 = Sprite is affine (attr1), 10 =
                             // Hidden, 11 = Affine using double rendering area
  uint32_t mGFXMode : 2;    // 00 = Normal, 01 = Alpha Blending, 10 = Masked for
                            // object window, 11 = Forbidden
  uint32_t mMosaic : 1;     // 0 = Off, 1 = On
  uint32_t mColorMode : 1;  // 0 = 4bpp, 1 = 8bpp
  uint32_t mSpriteShape : 2;  // See shape/size diagram

  /*
      Attribute 1
  */
  uint32_t mX : 9;  // Marks left of sprite
  uint32_t mAffineIndex : 5; // NOTE: Flipped state is also stored in this
  uint32_t mSpriteSize : 2;  // See shape/size diagram

  /*
     Attribute 3
  */
  uint32_t mTileIndex : 10;   // Sprite tile index (in bitmap mode this MUST be
                              // 512 or higher)
  uint32_t mZ : 2;            // Draw priority
  uint32_t mPalleteBankIndex : 4;  // Only used if mColorMode = 0

  /* SHAPE / SIZE diagram
  shape\size	00	    01	    10	    11
  00	        8x8	    16x16	  32x32	  64x64
  01	        16x8	  32x8	  32x16	  64x32
  10	        8x16	  8x32	  16x32	  32x64
  */

  /*
      Attribute 4
   */
  int16_t _fill;
} __attribute__ ((aligned (4))) SPRITE_OBJ;

typedef struct SPRITE_AFFINE {
  uint16_t _fill0[3];
  int16_t pa;
  uint16_t _fill1[3];
  int16_t pb;
  uint16_t _fill2[3];
  int16_t pc;
  uint16_t _fill3[3];
  int16_t pd;
} __attribute__ ((aligned (4))) SPRITE_AFFINE;