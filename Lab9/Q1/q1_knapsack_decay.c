#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { int id; double v, w, lam, d; } Item;

static int by_lambda_desc(const void *a, const void *b) {
    const Item *p = a, *q = b;
    if (p->lam != q->lam) return (p->lam > q->lam) ? -1 : 1;
    if (p->d != q->d)     return (p->d > q->d) ? -1 : 1;
    return p->id - q->id;
}
static double clip(double t, double hi) { return t < 0 ? 0 : (t > hi ? hi : t); }

/* Euclidean projection onto {0<=x<=w, sum x<=W} */
static void project(int n, const Item *it, const double *y, double W, double *x) {
    double s = 0;
    for (int i = 0; i < n; i++) { x[i] = clip(y[i], it[i].w); s += x[i]; }
    if (s <= W) return;
    double lo = 0, hi = 0;
    for (int i = 0; i < n; i++) if (y[i] > hi) hi = y[i];
    for (int k = 0; k < 100; k++) {
        double mid = 0.5 * (lo + hi); s = 0;
        for (int i = 0; i < n; i++) s += clip(y[i] - mid, it[i].w);
        if (s > W) lo = mid; else hi = mid;
    }
    for (int i = 0; i < n; i++) x[i] = clip(y[i] - hi, it[i].w);
}

/* g_k = d_k - lam_k * sum_{j<=k} x_j - sum_{j>k} lam_j x_j   (items sorted by lambda desc) */
static void gradient(int n, const Item *it, const double *x, double *g) {
    double suf = 0;
    for (int k = n - 1; k >= 0; k--) { g[k] = suf; suf += it[k].lam * x[k]; }
    double pre = 0;
    for (int k = 0; k < n; k++) { pre += x[k]; g[k] = it[k].d - it[k].lam * pre - g[k]; }
}

int main(void) {
    int n; double W;
    if (scanf("%d %lf", &n, &W) != 2 || n <= 0) { fprintf(stderr, "bad input\n"); return 1; }
    Item *it = malloc(n * sizeof *it);
    for (int i = 0; i < n; i++) {
        it[i].id = i + 1;
        if (scanf("%lf %lf %lf", &it[i].v, &it[i].w, &it[i].lam) != 3 || it[i].w <= 0 || it[i].lam <= 0) {
            fprintf(stderr, "bad item %d (need w>0, lambda>0)\n", i + 1); return 1; }
        it[i].d = it[i].v / it[i].w;
    }
    qsort(it, n, sizeof *it, by_lambda_desc);                       /* step 1: O(n log n) */

    double *x = calloc(n, sizeof *x), *xn = calloc(n, sizeof *xn), *y = calloc(n, sizeof *y),
           *z = calloc(n, sizeof *z), *g = calloc(n, sizeof *g);
    double L = 0; for (int i = 0; i < n; i++) L += it[i].lam;       /* trace(M) >= lambda_max(M) */
    double t = 1; int iter;
    for (iter = 1; iter <= 200000; iter++) {                         /* step 2 */
        gradient(n, it, y, g);
        for (int i = 0; i < n; i++) z[i] = y[i] + g[i] / L;
        project(n, it, z, W, xn);
        double tn = (1 + sqrt(1 + 4 * t * t)) / 2;
        for (int i = 0; i < n; i++) {
            y[i] = xn[i] + ((t - 1) / tn) * (xn[i] - x[i]);
            x[i] = xn[i];
        }
        t = tn;
        /* stop only when x is a fixed point of the projected-gradient map (true optimality test) */
        gradient(n, it, x, g);
        for (int i = 0; i < n; i++) z[i] = x[i] + g[i] / L;
        project(n, it, z, W, xn);
        double fp = 0;
        for (int i = 0; i < n; i++) if (fabs(xn[i] - x[i]) > fp) fp = fabs(xn[i] - x[i]);
        if (fp < 1e-12) break;
    }

    printf("Optimal consumption schedule (fastest-decaying first)\n");
    printf("%-5s %-9s %-10s %-10s %-10s %s\n", "item", "lambda", "start t", "amount", "fraction", "value");
    double T = 0, total = 0;
    for (int k = 0; k < n; k++) {
        if (x[k] < 1e-9) continue;
        double val = it[k].d * x[k] - it[k].lam * (T * x[k] + 0.5 * x[k] * x[k]);
        printf("%-5d %-9.4g %-10.4f %-10.4f %-10.4f %.4f\n", it[k].id, it[k].lam, T, x[k], x[k] / it[k].w, val);
        T += x[k]; total += val;
    }
    printf("Weight used = %.4f / %.4f\nMAXIMUM TOTAL VALUE = %.6f\n", T, W, total);

    /* ---- KKT certificate ---- */
    gradient(n, it, x, g);
    const double tol = 1e-7; int bind = (T >= W - 1e-7);
    double mu = 0, res = 0, sum_int = 0; int n_int = 0;
    for (int k = 0; k < n; k++) if (x[k] > tol && x[k] < it[k].w - tol) { sum_int += g[k]; n_int++; }
    if (bind && n_int) mu = sum_int / n_int;
    else if (bind) {
        double lo = 0, hi = 1e300;
        for (int k = 0; k < n; k++) { if (x[k] <= tol && g[k] > lo) lo = g[k]; if (x[k] >= it[k].w - tol && g[k] < hi) hi = g[k]; }
        if (lo > hi) res = lo - hi;
        mu = lo;
    }
    for (int k = 0; k < n; k++) {
        double r;
        if (x[k] <= tol) r = g[k] - mu; else if (x[k] >= it[k].w - tol) r = mu - g[k]; else r = fabs(g[k] - mu);
        if (r > res) res = r;
    }
    printf("[validation] FISTA iterations = %d, KKT residual = %.2e  (%s)\n", iter, res, res < 1e-5 ? "OPTIMAL" : "check");
    return 0;
}
