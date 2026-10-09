
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    char *s = malloc(1000001); int K;
    if (scanf("%1000000s %d", s, &K) != 2) { fprintf(stderr, "bad input\n"); return 1; }
    int n = (int)strlen(s), cnt[256] = {0}, last[256];
    for (int i = 0; i < n; i++) cnt[(unsigned char)s[i]]++;
    for (int c = 0; c < 256; c++) last[c] = -1;
    char *out = malloc(n + 1); int ok = 1;
    for (int i = 0; i < n && ok; i++) {
        int best = -1;
        if (K <= 1) { out[i] = s[i]; continue; }
        for (int c = 0; c < 256; c++) {
            if (cnt[c] <= 0 || (last[c] >= 0 && i - last[c] < K)) continue;
            if (best < 0 || cnt[c] > cnt[best] || (cnt[c] == cnt[best] && last[c] < last[best])) best = c;
        }
        if (best < 0) { ok = 0; break; }
        out[i] = (char)best; cnt[best]--; last[best] = i;
    }
    if (!ok) { printf("Result: \"\" (impossible for K=%d)\n", K); return 0; }
    out[n] = 0; printf("Result: %s\n", out);
    /* validation: same multiset + min gap */
    int c1[256] = {0}, c2[256] = {0}, pos[256], gapok = 1; for (int c = 0; c < 256; c++) pos[c] = -1;
    for (int i = 0; i < n; i++) { c1[(unsigned char)s[i]]++; c2[(unsigned char)out[i]]++;
        unsigned char ch = out[i]; if (pos[ch] >= 0 && i - pos[ch] < K) gapok = 0; pos[ch] = i; }
    printf("[validation] permutation of input: %s, all gaps >= %d: %s\n", memcmp(c1, c2, sizeof c1) ? "NO" : "yes", K, gapok ? "yes" : "NO");
    return 0;
}
