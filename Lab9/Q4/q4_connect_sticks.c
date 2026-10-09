
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;
static ll *h; static int hs;
static void push(ll v) { int i = hs++; h[i] = v; while (i && h[i] < h[(i - 1) / 2]) { int p = (i - 1) / 2; ll t = h[i]; h[i] = h[p]; h[p] = t; i = p; } }
static ll pop(void) { ll top = h[0]; h[0] = h[--hs]; int i = 0;
    for (;;) { int l = 2 * i + 1, r = l + 1, m = i; if (l < hs && h[l] < h[m]) m = l; if (r < hs && h[r] < h[m]) m = r;
        if (m == i) break; ll t = h[i]; h[i] = h[m]; h[m] = t; i = m; } return top; }

int main(void) {
    int n; if (scanf("%d", &n) != 1 || n < 1) { fprintf(stderr, "bad n\n"); return 1; }
    ll *a = malloc(n * sizeof *a); h = malloc(n * sizeof *h);
    for (int i = 0; i < n; i++) { if (scanf("%lld", &a[i]) != 1 || a[i] < 0) { fprintf(stderr, "bad length\n"); return 1; } push(a[i]); }
    ll cost = 0;
    while (hs > 1) { ll x = pop(), y = pop(); cost += x + y; push(x + y); }
    printf("Minimum total cost = %lld\n", cost);
    if (n <= 3000) {
        int m = n; ll c2 = 0;
        while (m > 1) { int i1 = 0, i2 = 1; if (a[i2] < a[i1]) { i1 = 1; i2 = 0; }
            for (int k = 2; k < m; k++) { if (a[k] < a[i1]) { i2 = i1; i1 = k; } else if (a[k] < a[i2]) i2 = k; }
            ll s = a[i1] + a[i2]; c2 += s; int hi = i1 > i2 ? i1 : i2, lo = i1 < i2 ? i1 : i2;
            a[lo] = s; a[hi] = a[m - 1]; m--; }
        printf("[validation] naive O(n^2) merge = %lld  (%s)\n", c2, c2 == cost ? "MATCH" : "MISMATCH");
    }
    return 0;
}
