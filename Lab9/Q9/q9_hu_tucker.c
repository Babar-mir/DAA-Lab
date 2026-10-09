
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXN 200
typedef long long ll;
typedef struct { ll w; int l, r, sq; } HN;
static HN t[2 * MAXN];
static int lev[MAXN];
static void dfs(int u, int d) { if (t[u].l < 0) { lev[u] = d; return; } dfs(t[u].l, d + 1); dfs(t[u].r, d + 1); }

static int L2[2 * MAXN], R2[2 * MAXN];          /* phase-2 tree */
static void show(int u, int n) { if (u < n) { printf("%d", u + 1); return; } printf("("); show(L2[u], n); printf(" "); show(R2[u], n); printf(")"); }

int main(void) {
    int n; static ll w[MAXN];
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { fprintf(stderr, "bad n (1..%d)\n", MAXN); return 1; }
    for (int i = 0; i < n; i++) if (scanf("%lld", &w[i]) != 1 || w[i] < 0) { fprintf(stderr, "bad weight\n"); return 1; }

    int cur[MAXN], m = n, nn = n;
    for (int i = 0; i < n; i++) { t[i] = (HN){ w[i], -1, -1, 1 }; cur[i] = i; }
    while (m > 1) {
        ll best = LLONG_MAX; int bi = -1, bj = -1;
        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < m; j++) {
                ll s = t[cur[i]].w + t[cur[j]].w;
                if (s < best) { best = s; bi = i; bj = j; }
                if (t[cur[j]].sq) break;                  /* cannot look past a square node */
            }
        t[nn] = (HN){ best, cur[bi], cur[bj], 0 };
        cur[bi] = nn++;
        for (int k = bj; k + 1 < m; k++) cur[k] = cur[k + 1];
        m--;
    }
    dfs(cur[0], 0);

    /* phase 2 */
    int st[MAXN], sl[MAXN], sp = 0, nn2 = n;
    for (int i = 0; i < n; i++) {
        st[sp] = i; sl[sp] = lev[i]; sp++;
        while (sp >= 2 && sl[sp - 1] == sl[sp - 2]) {
            L2[nn2] = st[sp - 2]; R2[nn2] = st[sp - 1];
            st[sp - 2] = nn2++; sl[sp - 2]--; sp--;
        }
    }
    ll cost = 0; for (int i = 0; i < n; i++) cost += w[i] * lev[i];
    printf("Leaf depths (in input order):"); for (int i = 0; i < n; i++) printf(" %d", lev[i]);
    printf("\nAlphabetic tree: "); if (sp == 1 && sl[0] == 0) show(st[0], n); else printf("(reconstruction failed)");
    printf("\nOptimal cost sum(w_i*depth_i) = %lld\n", cost);

    /* DP validation */
    static ll C[MAXN][MAXN], P[MAXN + 1];
    P[0] = 0; for (int i = 0; i < n; i++) P[i + 1] = P[i] + w[i];
    for (int i = 0; i < n; i++) C[i][i] = 0;
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) { int j = i + len - 1; ll b = LLONG_MAX;
            for (int k = i; k < j; k++) { ll v = C[i][k] + C[k + 1][j]; if (v < b) b = v; }
            C[i][j] = b + P[j + 1] - P[i]; }
    printf("[validation] interval-DP optimum = %lld  (%s)\n", C[0][n - 1], C[0][n - 1] == cost ? "MATCH" : "MISMATCH");
    return 0;
}
