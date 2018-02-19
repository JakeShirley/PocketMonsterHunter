#include "mosaic.h"

static uint32_t *const REG_MOSAIC = ((uint32_t*)0x400004C);

void Mosaic_setSpriteStretch(uint8_t horizontal, uint8_t vertical) {
    *REG_MOSAIC = 
    ((horizontal & 0xf) << 8) |
    ((vertical & 0xf) << 12);
}