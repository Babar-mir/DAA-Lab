
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
static ll *h; static int hs;
static void push(ll v) { int i = hs++; h[i] = v; while (i && h[i] > h[(i - 1) / 2]) { int p = (i - 1) / 2; ll t = h[i]; h[i] = h[p]; h[p] = t; i = p; } }
static ll pop(void) { ll top = h[0]; h[0] = h[--hs]; int i = 0;
    for (;;) { int l = 2 * i + 1, r = l + 1, m = i; if (l < hs && h[l] > h[m]) m = l; if (r < hs && h[r] > h[m]) m = r;
        if (m == i) break; ll t = h[i]; h[i] = h[m]; h[m] = t; i = m; } return top; }
int main(void) {
    int n; if (scanf("%d", &n) != 1 || n < 1) { fprintf(stderr, "bad n\n"); return 1; }
    h = malloc(n * sizeof *h); ll mn = -1;
    for (int i = 0; i < n; i++) { ll a; if (scanf("%lld", &a) != 1 || a <= 0) { fprintf(stderr, "need positive ints\n"); return 1; }
        if (a & 1) a *= 2; push(a); if (mn < 0 || a < mn) mn = a; }
    ll best = h[0] - mn;
    for (;;) { ll mx = pop(); if (mx - mn < best) best = mx - mn;
        if (mx & 1) break;
        mx /= 2; if (mx < mn) mn = mx; push(mx); }
    printf("Minimum deviation = %lld\n", best);
    return 0;
}
