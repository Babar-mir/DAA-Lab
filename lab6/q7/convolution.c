#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI acos(-1.0)

void fft(double complex a[], int n, int invert)
{
    if (n == 1)
        return;

    double complex even[n / 2];
    double complex odd[n / 2];

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    double angle = 2 * PI / n;

    if (invert)
        angle = -angle;

    double complex w = 1;
    double complex wn = cos(angle) + I * sin(angle);

    for (int i = 0; i < n / 2; i++)
    {
        double complex t = w * odd[i];

        a[i] = even[i] + t;
        a[i + n / 2] = even[i] - t;

        w *= wn;
    }

    if (invert)
    {
        for (int i = 0; i < n; i++)
            a[i] /= 2;
    }
}

int nextPowerOfTwo(int n)
{
    int power = 1;

    while (power < n)
        power *= 2;

    return power;
}

int main()
{
    int m, n;

    printf("Enter size of vector A: ");
    scanf("%d", &m);

    printf("Enter size of vector B: ");
    scanf("%d", &n);

    if (m <= 0 || n <= 0)
    {
        printf("Invalid vector size.\n");
        return 0;
    }

    if (n < m)
    {
        printf("Condition n >= m is required.\n");
        return 0;
    }

    int resultSize = m + n - 1;

    int size = nextPowerOfTwo(resultSize);

    double complex A[size];
    double complex B[size];

    for (int i = 0; i < size; i++)
    {
        A[i] = 0;
        B[i] = 0;
    }

    printf("Enter elements of A:\n");

    for (int i = 0; i < m; i++)
    {
        double x;
        scanf("%lf", &x);
        A[i] = x;
    }

    printf("Enter elements of B:\n");

    for (int i = 0; i < n; i++)
    {
        double x;
        scanf("%lf", &x);
        B[i] = x;
    }

    /* FFT */
    fft(A, size, 0);
    fft(B, size, 0);

    /* Point-wise multiplication */
    for (int i = 0; i < size; i++)
        A[i] = A[i] * B[i];

    /* Inverse FFT */
    fft(A, size, 1);

    printf("\nConvolution:\n");

    for (int i = 0; i < resultSize; i++)
    {
        printf("%.2lf ", creal(A[i]));
    }

    printf("\n");

    return 0;
}