#include "rvv.h"

void alpha_compositing_rvv(uint8_t* foreground, uint8_t* background, float alpha, uint8_t* dst, int width, int height, int channels) {
    // Just a placeholder
    alpha_compositing_scalar(foreground, background, alpha, dst, width, height, channels);
}
