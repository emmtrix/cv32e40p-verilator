#include <math.h>
#include <stdio.h>

int main(void) {
    float s = sinf(0.5f);
    float r = sqrtf(9.0f);
    float e = expf(1.0f);

    if ((s > 0.479f && s < 0.480f) &&
        (r > 2.999f && r < 3.001f) &&
        (e > 2.718f && e < 2.719f)) {
        printf("MATH LIB PASS sin=%0.6f sqrt=%0.6f exp=%0.6f\n", (double)s, (double)r, (double)e);
        return 0;
    }

    printf("MATH LIB FAIL sin=%0.6f sqrt=%0.6f exp=%0.6f\n", (double)s, (double)r, (double)e);
    return 1;
}
