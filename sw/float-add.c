#include <stdio.h>

int main(void) {
    volatile float a = 1.25f;
    volatile float b = 2.50f;
    volatile float c = a + b;

    if (c > 3.749f && c < 3.751f) {
        printf("FLOAT ADD PASS c=%0.3f\n", (double)c);
        return 0;
    }

    printf("FLOAT ADD FAIL c=%0.6f\n", (double)c);
    return 1;
}
