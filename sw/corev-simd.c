#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

int main(void) {
    uint32_t a = 0x00020001u;
    uint32_t b = 0x00040003u;
    uint32_t out;

    __asm__ volatile("cv.add.h %0, %1, %2"
                     : "=r"(out)
                     : "r"(a), "r"(b));

    uint16_t lo = (uint16_t)(out & 0xFFFFu);
    uint16_t hi = (uint16_t)((out >> 16) & 0xFFFFu);

    if (lo == 4u && hi == 6u) {
        printf("COREV SIMD PASS out=0x%08" PRIx32 "\n", out);
        return 0;
    }

    printf("COREV SIMD FAIL out=0x%08" PRIx32 "\n", out);
    return 1;
}
