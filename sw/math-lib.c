#include <math.h>
#include <stdio.h>

int main(void) {
    volatile float x = 0.5f;
    volatile float y = 9.0f;
    volatile float z = 1.0f;
    
    float s = sinf(x);
    float r = sqrtf(y);
    float e = expf(z);
    float m = fmaxf(s, r);

    if ((s > 0.479f && s < 0.480f) &&
        (r > 2.999f && r < 3.001f) &&
        (e > 2.718f && e < 2.719f) &&
        (m > 2.999f && m < 3.001f)) {
        printf("MATH LIB PASS sin=%0.6f sqrt=%0.6f exp=%0.6f max=%0.6f\n", (double)s, (double)r, (double)e, (double)m);
        return 0;
    }

    printf("MATH LIB FAIL sin=%0.6f sqrt=%0.6f exp=%0.6f max=%0.6f\n", (double)s, (double)r, (double)e, (double)m);
    return 1;
}
