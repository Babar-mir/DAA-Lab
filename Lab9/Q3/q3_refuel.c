
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
typedef struct { ll d, f; } St;
static int cmp(const void *a, const void *b) { ll x = ((const St *)a)->d, y = ((const St *)b)->d; return (x > y) - (x < y); }
static ll *hp; static int hs;
static void push(ll v) { int i = hs++; hp[i] = v; while (i && hp[i] > hp[(i - 1) / 2]) { int p = (i - 1) / 2; ll t = hp[i]; hp[i] = hp[p]; hp[p] = t; i = p; } }
static ll pop(void) { ll top = hp[0]; hp[0] = hp[--hs]; int i = 0;
    for (;;) { int l = 2 * i + 1, r = l + 1, m = i; if (l < hs && hp[l] > hp[m]) m = l; if (r < hs && hp[r] > hp[m]) m = r;
        if (m == i) break; ll t = hp[i]; hp[i] = hp[m]; hp[m] = t; i = m; } return top; }

int main(void) {
    ll D, F; int n;
    if (scanf("%lld %lld %d", &D, &F, &n) != 3 || n < 0) { fprintf(stderr, "bad input\n"); return 1; }
    St *s = malloc((n + 1) * sizeof *s); hp = malloc((n + 1) * sizeof *hp);
    for (int i = 0; i < n; i++) if (scanf("%lld %lld", &s[i].d, &s[i].f) != 2) { fprintf(stderr, "bad station\n"); return 1; }
    qsort(s, n, sizeof *s, cmp);

    ll reach = F; int i = 0, stops = 0, ok = 1;
    while (reach < D) {
        while (i < n && s[i].d <= reach) push(s[i++].f);
        if (!hs) { ok = 0; break; }
        reach += pop(); stops++;
    }
    if (ok) printf("Minimum refuelling stops (greedy)   = %d\n", stops); else printf("Minimum refuelling stops (greedy)   = -1 (unreachable)\n");

    /* DP cross-check */
    ll *dp = malloc((n + 1) * sizeof *dp); for (int j = 0; j <= n; j++) dp[j] = -1; dp[0] = F;
    for (int k = 0; k < n; k++) for (int j = k + 1; j >= 1; j--) if (dp[j - 1] >= s[k].d && dp[j - 1] + s[k].f > dp[j]) dp[j] = dp[j - 1] + s[k].f;
    int dpans = -1; for (int j = 0; j <= n; j++) if (dp[j] >= D) { dpans = j; break; }
    printf("[validation] DP answer              = %d  (%s)\n", dpans, dpans == (ok ? stops : -1) ? "MATCH" : "MISMATCH");

    ll R = D; for (int k = n - 1; k >= 0; k--) { ll t = R - s[k].f; R = t > s[k].d ? t : s[k].d; }
    printf("Reverse greedy: minimum initial fuel needed to reach D (stopping everywhere) = %lld\n", R);
    return 0;
}
