
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXS 256
typedef struct { long long f; int l, r, ord; } Node;
static Node nd[2 * MAXS];
static int heap[2 * MAXS], hs;
static int len[MAXS];

static int less(int a, int b) { return nd[a].f != nd[b].f ? nd[a].f < nd[b].f : nd[a].ord < nd[b].ord; }
static void hpush(int v) { int i = hs++; heap[i] = v;
    while (i && less(heap[i], heap[(i - 1) / 2])) { int p = (i - 1) / 2, t = heap[i]; heap[i] = heap[p]; heap[p] = t; i = p; } }
static int hpop(void) { int top = heap[0]; heap[0] = heap[--hs]; int i = 0;
    for (;;) { int l = 2 * i + 1, r = l + 1, m = i;
        if (l < hs && less(heap[l], heap[m])) m = l;
        if (r < hs && less(heap[r], heap[m])) m = r;
        if (m == i) break; int t = heap[i]; heap[i] = heap[m]; heap[m] = t; i = m; }
    return top; }
static void dfs(int u, int d) { if (nd[u].l < 0) { len[u] = d; return; } dfs(nd[u].l, d + 1); dfs(nd[u].r, d + 1); }

static char sym[MAXS]; static long long fr[MAXS];
static int ord_idx[MAXS];
static int cmp(const void *a, const void *b) { int i = *(const int *)a, j = *(const int *)b;
    if (len[i] != len[j]) return len[i] - len[j]; return (unsigned char)sym[i] - (unsigned char)sym[j]; }

int main(void) {
    int n; if (scanf("%d", &n) != 1 || n < 1 || n > MAXS) { fprintf(stderr, "bad n (1..%d)\n", MAXS); return 1; }
    long long total = 0;
    for (int i = 0; i < n; i++) { if (scanf(" %c %lld", &sym[i], &fr[i]) != 2 || fr[i] < 0) { fprintf(stderr, "bad input\n"); return 1; }
        nd[i] = (Node){ fr[i], -1, -1, i }; hpush(i); total += fr[i]; }
    int cnt = n;
    while (hs > 1) { int a = hpop(), b = hpop();
        nd[cnt] = (Node){ nd[a].f + nd[b].f, a, b, cnt }; hpush(cnt++); }
    if (n == 1) len[0] = 1; else dfs(heap[0], 0);

    for (int i = 0; i < n; i++) ord_idx[i] = i;
    qsort(ord_idx, n, sizeof(int), cmp);

    char code[MAXS + 2]; int cl = 0; code[0] = 0;
    double kraft = 0, expl = 0, H = 0;
    printf("Canonical Huffman codebook\n%-7s %-10s %-4s %s\n", "symbol", "freq", "len", "code");
    for (int k = 0; k < n; k++) { int i = ord_idx[k];
        if (k == 0) { cl = len[i]; memset(code, '0', cl); }
        else { int p = cl - 1; while (p >= 0 && code[p] == '1') code[p--] = '0'; if (p >= 0) code[p] = '1';  /* +1 */
               while (cl < len[i]) code[cl++] = '0'; }                                                       /* << */
        code[cl] = 0;
        printf("%-7c %-10lld %-4d %s\n", sym[i], fr[i], len[i], code);
        kraft += ldexp(1.0, -len[i]);
        expl += (double)fr[i] * len[i];
        if (fr[i] > 0 && total > 0) { double p = (double)fr[i] / total; H -= p * log2(p); }
    }
    printf("Total encoded bits = %.0f\n", expl);
    if (total > 0) printf("Expected length = %.6f bits/symbol, entropy = %.6f  (H <= L < H+1)\n", expl / total, H);
    printf("[validation] Kraft sum = %.12f  (%s)\n", kraft, fabs(kraft - 1) < 1e-9 ? "complete prefix code" : (n == 1 ? "single symbol" : "NOT 1"));
    return 0;
}
