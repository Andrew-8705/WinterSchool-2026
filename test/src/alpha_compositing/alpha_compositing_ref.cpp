#include "alpha_compositing_test.hpp"

void alpha_compositing_ref(uint8_t* foreground, uint8_t* background, float alpha, uint8_t* dst, int width, int height, int channels) {
    int pixelNum = width * height;

    for (int i = 0; i < pixelNum; ++i) {
        for (int c = 0; c < channels; ++c) {
            int idx = i * channels + c;
            dst[idx] = (uint8_t)(
                foreground[idx] * alpha + background[idx] * (1.0f - alpha)
            );
        }
    }
}
