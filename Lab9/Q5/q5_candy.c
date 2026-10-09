
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
int main(void) {
    int n; if (scanf("%d", &n) != 1 || n < 1) { fprintf(stderr, "bad n\n"); return 1; }
    int *r = malloc(n * sizeof *r), *c = malloc(n * sizeof *c);
    for (int i = 0; i < n; i++) if (scanf("%d", &r[i]) != 1) { fprintf(stderr, "bad rating\n"); return 1; }
    for (int i = 0; i < n; i++) c[i] = 1;
    for (int i = 1; i < n; i++) if (r[i] > r[i - 1]) c[i] = c[i - 1] + 1;
    for (int i = n - 2; i >= 0; i--) if (r[i] > r[i + 1] && c[i] <= c[i + 1]) c[i] = c[i + 1] + 1;
    ll total = 0; for (int i = 0; i < n; i++) total += c[i];
    printf("Candies per child:"); for (int i = 0; i < n; i++) printf(" %d", c[i]);
    printf("\nMinimum total candies = %lld\n", total);

    ll t2 = 1; int up = 0, down = 0, peak = 0;
    for (int i = 1; i < n; i++) {
        if (r[i] > r[i - 1])       { up++; down = 0; peak = up; t2 += 1 + up; }
        else if (r[i] == r[i - 1]) { up = down = peak = 0; t2 += 1; }
        else                       { up = 0; down++; t2 += 1 + down; if (peak >= down) t2--; }
    }
    printf("[validation] one-pass slope method = %lld  (%s)\n", t2, t2 == total ? "MATCH" : "MISMATCH");
    int ok = 1;
    for (int i = 0; i < n; i++) { if (i && r[i] > r[i - 1] && c[i] <= c[i - 1]) ok = 0; if (i + 1 < n && r[i] > r[i + 1] && c[i] <= c[i + 1]) ok = 0; }
    printf("[validation] rule check on assignment: %s\n", ok ? "OK" : "VIOLATED");
    return 0;
}
