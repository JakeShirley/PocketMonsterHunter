#pragma once

// stl
#include <stdint.h>
#include <string.h> // memcpy

// tonc
#include "tonc_memdef.h"
#include "tonc_memmap.h"

typedef struct BG_CONTROL {
  uint32_t mZ : 1;                   // Draw order
  uint32_t mCharacterBaseBlock : 2;  // Charblock index for tile palette (0-3)
  uint32_t mMosaic : 1;              // Mosaic mode
  uint32_t mColorMode : 1;           // 0 = 4bpp (16-bit color), 1 =  8bpp
  uint32_t mScreenBaseBlock : 5;     // Screenblock index for tile ids (0-31)
  uint32_t
      mBackgroundSize : 2;  // Sets tile size, different if we're an affine BG

  /* Regular
  Sz-flag	define	(tiles)	(pixels)
  00	BG_REG_32x32	32x32	256x256
  01	BG_REG_64x32	64x32	512x256
  10	BG_REG_32x64	32x64	256x512
  11	BG_REG_64x64	64x64	512x512
  */

  /* Affine
  Sz-flag	define	(tiles)	(pixels)
  00	BG_AFF_16x16	16x16	128x128
  01	BG_AFF_32x32	32x32	256x256
  10	BG_AFF_64x64	64x64	512x512
  11	BG_AFF_128x128	128x128	1024x1024
  */
} BG_CONTROL;

typedef struct BG_TILE {
  uint32_t mTileIndex : 10; // Tile index (0-1023)
  uint32_t mHorizontalFlip : 1;  // (0=Normal, 1=Mirrored)
  uint32_t mVerticalFlip : 1;  // (0=Normal, 1=Mirrored)
  uint32_t mPaletteIndex : 4; // Palette index (0-15) (Not used in 256 color/1 palette mode)
} BG_TILE;

void testbg();