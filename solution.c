#include <stdio.h>
#include <math.h>

int main() {
    int T, L, D, m;
    double b;
    scanf("%d %d %d %lf %d", &T, &L, &D, &b, &m);

    double x[256];
    for (int i = 0; i < D; i++) {
        scanf("%lf", &x[i]);
    }

    double s = (double)T / L;
    if (s < 1.0) {
        s = 1.0;
    }
    double b_prime = b * pow(s, (double)D / (D - 2));

    double out[256];
    for (int d = 0; d < D; d += 2) {
        int i = d / 2;
        double theta = m * pow(b_prime, -2.0 * i / D);
        double c = cos(theta);
        double snt = sin(theta);
        out[d] = x[d] * c - x[d + 1] * snt;
        out[d + 1] = x[d] * snt + x[d + 1] * c;
    }

    for (int i = 0; i < D; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%.4f", out[i]);
    }
    printf("\n");

    return 0;
}
