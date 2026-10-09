
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
static int cmp(const void *a, const void *b) { ll x = *(const ll *)a, y = *(const ll *)b; return (x > y) - (x < y); }
int main(void) {
    int n; if (scanf("%d", &n) != 1 || n < 0) { fprintf(stderr, "bad n\n"); return 1; }
    ll *s = malloc((n + 1) * sizeof *s), *e = malloc((n + 1) * sizeof *e), *S = malloc((n + 1) * sizeof *S), *E = malloc((n + 1) * sizeof *E);
    for (int i = 0; i < n; i++) { if (scanf("%lld %lld", &s[i], &e[i]) != 2 || s[i] >= e[i]) { fprintf(stderr, "bad interval %d (need s<e)\n", i + 1); return 1; } S[i] = s[i]; E[i] = e[i]; }
    qsort(S, n, sizeof(ll), cmp); qsort(E, n, sizeof(ll), cmp);
    int i = 0, j = 0, rooms = 0, best = 0;
    while (i < n) { if (S[i] < E[j]) { rooms++; i++; if (rooms > best) best = rooms; } else { rooms--; j++; } }
    printf("Minimum meeting rooms = %d\n", best);
    int b2 = 0;
    for (int a = 0; a < n; a++) { int c = 0; for (int k = 0; k < n; k++) if (s[k] <= s[a] && s[a] < e[k]) c++; if (c > b2) b2 = c; }
    printf("[validation] brute-force max overlap = %d  (%s)\n", b2, b2 == best ? "MATCH" : "MISMATCH");
    return 0;
}
