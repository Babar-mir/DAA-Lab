#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    char str1[100], str2[100];

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    int m = strlen(str1);
    int n = strlen(str2);

    int dp[m + 1][n + 1];

    /* Initialize DP table */
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            dp[i][j] = 0;
        }
    }

    /* Fill DP table */
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int length = dp[m][n];

    char lcs[length + 1];

    lcs[length] = '\0';

    int i = m;
    int j = n;
    int index = length - 1;

    /* Reconstruct LCS */
    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            lcs[index] = str1[i - 1];

            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("\nLength of LCS = %d\n", length);
    printf("Longest Common Subsequence = %s\n", lcs);

    return 0;
}