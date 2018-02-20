#include "tile_layer.h"

// PMH
#include "assets_tileset_sand.h"

#include "brin.h"

void testbg() {
  // Load palette
  memcpy(pal_bg_mem, assets_tileset_sandPal, assets_tileset_sandPalLen);
  // Load tiles into CBB 0 (TODO: Get this index working)
  memcpy(&tile_mem[0][0], assets_tileset_sandTiles,
         assets_tileset_sandTilesLen);

  memcpy(&se_mem[30][0], assets_tileset_sandMap, assets_tileset_sandMapLen);

//   BG_TILE testTiles[64];
//   for (int i = 0; i < 64; ++i) {
//     testTiles[i].mTileIndex = 1;
//     testTiles[i].mHorizontalFlip = false;
//     testTiles[i].mVerticalFlip = false;
//     testTiles[i].mPaletteIndex = 0;
//   }

  // Load map into SBB 30
  //memcpy(&se_mem[30][0], &testTiles, sizeof(testTiles));

  REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32;
}