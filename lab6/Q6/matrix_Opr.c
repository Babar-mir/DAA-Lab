#include <stdio.h>
#include <math.h>

#define MAX 50

void printMatrix(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%.2lf ", A[i][j]);

        printf("\n");
    }
}

void addMatrix(double A[MAX][MAX],
               double B[MAX][MAX],
               double C[MAX][MAX],
               int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}

void multiplyMatrix(double A[MAX][MAX],
                    double B[MAX][MAX],
                    double C[MAX][MAX],
                    int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int isZeroMatrix(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != 0)
                return 0;
        }
    }

    return 1;
}

int isSymmetric(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (A[i][j] != A[j][i])
                return 0;
        }
    }

    return 1;
}

double determinant(double A[MAX][MAX], int n)
{
    double temp[MAX][MAX];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = A[i][j];

    double det = 1;

    for (int i = 0; i < n; i++)
    {
        int pivot = i;

        for (int j = i + 1; j < n; j++)
        {
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
                pivot = j;
        }

        if (fabs(temp[pivot][i]) < 1e-9)
            return 0;

        if (pivot != i)
        {
            for (int j = 0; j < n; j++)
            {
                double t = temp[i][j];
                temp[i][j] = temp[pivot][j];
                temp[pivot][j] = t;
            }

            det = -det;
        }

        det *= temp[i][i];

        for (int j = i + 1; j < n; j++)
        {
            double factor = temp[j][i] / temp[i][i];

            for (int k = i; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }
    }

    return det;
}

void transpose(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/* Power Iteration for dominant eigenvalue */
void dominantEigen(double A[MAX][MAX], int n)
{
    double x[MAX];

    for (int i = 0; i < n; i++)
        x[i] = 1.0;

    double eigenvalue = 0;

    for (int iteration = 0; iteration < 1000; iteration++)
    {
        double y[MAX];

        for (int i = 0; i < n; i++)
        {
            y[i] = 0;

            for (int j = 0; j < n; j++)
                y[i] += A[i][j] * x[j];
        }

        double maxValue = fabs(y[0]);

        for (int i = 1; i < n; i++)
        {
            if (fabs(y[i]) > maxValue)
                maxValue = fabs(y[i]);
        }

        if (maxValue == 0)
        {
            printf("Cannot determine eigenvalue.\n");
            return;
        }

        for (int i = 0; i < n; i++)
            x[i] = y[i] / maxValue;

        eigenvalue = maxValue;
    }

    printf("\nDominant Eigenvalue = %.4lf\n", eigenvalue);

    printf("Corresponding Eigenvector:\n");

    for (int i = 0; i < n; i++)
        printf("%.4lf\n", x[i]);
}

int main()
{
    int n;

    double A[MAX][MAX];
    double B[MAX][MAX];
    double C[MAX][MAX];

    printf("Enter order of square matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid matrix size.\n");
        return 0;
    }

    printf("\nEnter Matrix A:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);
    }

    printf("\nEnter Matrix B:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%lf", &B[i][j]);
    }

    /* Addition */
    addMatrix(A, B, C, n);

    printf("\nMatrix Addition:\n");
    printMatrix(C, n);

    /* Multiplication */
    multiplyMatrix(A, B, C, n);

    printf("\nMatrix Multiplication:\n");
    printMatrix(C, n);

    /* Zero matrix */
    if (isZeroMatrix(A, n))
        printf("\nA is a zero matrix.\n");
    else
        printf("\nA is not a zero matrix.\n");

    /* Symmetric */
    if (isSymmetric(A, n))
        printf("A is symmetric.\n");
    else
        printf("A is not symmetric.\n");

    /* Determinant */
    printf("Determinant of A = %.2lf\n",
           determinant(A, n));

    /* Transpose */
    transpose(A, n);

    printf("\nTranspose of A:\n");
    printMatrix(A, n);

    /* Eigenvalue/eigenvector */
    dominantEigen(A, n);

    return 0;
}