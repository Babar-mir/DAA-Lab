
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 16
#define MAXL 128
#define MAXT (MAXN * MAXL + 8)

static int overlap(const char *a, const char *b) {
    int la = (int)strlen(a), lb = (int)strlen(b), m = la < lb ? la : lb;
    for (int k = m; k > 0; k--) if (strncmp(a + la - k, b, k) == 0) return k;
    return 0;
}
/* drop duplicates and strings contained in another one; returns new count */
static int preprocess(char s[][MAXL], int n) {
    int keep[MAXN], m = 0; char tmp[MAXN][MAXL];
    for (int i = 0; i < n; i++) { keep[i] = 1;
        for (int j = 0; j < n && keep[i]; j++) {
            if (i == j || !strstr(s[j], s[i])) continue;
            if (strcmp(s[i], s[j]) == 0 && i < j) continue;   /* duplicates: keep the first */
            keep[i] = 0; } }
    for (int i = 0; i < n; i++) if (keep[i]) strcpy(tmp[m++], s[i]);
    for (int i = 0; i < m; i++) strcpy(s[i], tmp[i]);
    return m;
}
static int greedy(char s[][MAXL], int n, char *out) {
    static char buf[MAXN][MAXT]; int m = n;
    for (int i = 0; i < n; i++) strcpy(buf[i], s[i]);
    while (m > 1) {
        int bi = 0, bj = 1, bo = -1;
        for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) { if (i == j) continue;
            int o = overlap(buf[i], buf[j]); if (o > bo) { bo = o; bi = i; bj = j; } }
        strcat(buf[bi], buf[bj] + bo);
        if (bj != m - 1) strcpy(buf[bj], buf[m - 1]);
        m--;
    }
    strcpy(out, buf[0]); return (int)strlen(out);
}
static int exact(char s[][MAXL], int n, char *out) {
    static int ov[MAXN][MAXN]; int len[MAXN];
    for (int i = 0; i < n; i++) { len[i] = (int)strlen(s[i]); for (int j = 0; j < n; j++) ov[i][j] = i == j ? 0 : overlap(s[i], s[j]); }
    int full = (1 << n) - 1; size_t sz = (size_t)(full + 1) * n;
    int *dp = malloc(sz * sizeof *dp); signed char *par = malloc(sz);
    for (size_t k = 0; k < sz; k++) { dp[k] = 1 << 29; par[k] = -1; }
    for (int i = 0; i < n; i++) dp[(1 << i) * n + i] = len[i];
    for (int mask = 1; mask <= full; mask++) for (int i = 0; i < n; i++) {
        int cur = dp[mask * n + i]; if (cur >= (1 << 29) || !(mask >> i & 1)) continue;
        for (int j = 0; j < n; j++) if (!(mask >> j & 1)) { int nm = mask | 1 << j, v = cur + len[j] - ov[i][j];
            if (v < dp[nm * n + j]) { dp[nm * n + j] = v; par[nm * n + j] = (signed char)i; } } }
    int bl = 1 << 29, bl_i = 0; for (int i = 0; i < n; i++) if (dp[full * n + i] < bl) { bl = dp[full * n + i]; bl_i = i; }
    int order[MAXN], mask = full, i = bl_i;
    for (int k = n - 1; k >= 0; k--) { order[k] = i; int p = par[mask * n + i]; mask ^= 1 << i; i = p; }
    strcpy(out, s[order[0]]);
    for (int k = 1; k < n; k++) strcat(out, s[order[k]] + ov[order[k - 1]][order[k]]);
    free(dp); free(par); return bl;
}

int main(int argc, char **argv) {
    static char s[MAXN][MAXL], g[MAXT], o[MAXT];
    if (argc >= 2 && strcmp(argv[1], "--search") == 0) {
        if (argc != 7) { fprintf(stderr, "usage: %s --search trials n maxlen alphabet seed\n", argv[0]); return 1; }
        int trials = atoi(argv[2]), n = atoi(argv[3]), ml = atoi(argv[4]), al = atoi(argv[5]); srand(atoi(argv[6]));
        if (n > MAXN || ml >= MAXL || al < 1 || al > 26) { fprintf(stderr, "limits: n<=%d, maxlen<%d, alphabet<=26\n", MAXN, MAXL); return 1; }
        double worst = 0; char ws[MAXN][MAXL]; int wn = 0, wg = 0, wo = 0;
        for (int t = 0; t < trials; t++) {
            for (int i = 0; i < n; i++) { int l = 2 + rand() % (ml - 1); for (int k = 0; k < l; k++) s[i][k] = 'a' + rand() % al; s[i][l] = 0; }
            int m = preprocess(s, n); int gl = greedy(s, m, g), ol = exact(s, m, o);
            double r = (double)gl / ol;
            if (r > worst) { worst = r; wn = m; wg = gl; wo = ol; for (int i = 0; i < m; i++) strcpy(ws[i], s[i]); }
        }
        printf("Worst ratio over %d random instances: %.4f (greedy=%d, optimal=%d)\nInstance:", trials, worst, wg, wo);
        for (int i = 0; i < wn; i++) printf(" %s", ws[i]); printf("\n");
        return 0;
    }
    int n; if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { fprintf(stderr, "bad n (1..%d)\n", MAXN); return 1; }
    for (int i = 0; i < n; i++) if (scanf("%127s", s[i]) != 1) { fprintf(stderr, "bad string\n"); return 1; }
    int m = preprocess(s, n);
    int gl = greedy(s, m, g), ol = exact(s, m, o);
    printf("After removing contained/duplicate strings: %d strings\n", m);
    printf("Greedy superstring  (len %d): %s\n", gl, g);
    printf("Optimal superstring (len %d): %s\n", ol, o);
    printf("Approximation ratio greedy/optimal = %.4f   (conjecture says <= 2; handout claims a counterexample approaching 2.25)\n", (double)gl / ol);
    return 0;
}
