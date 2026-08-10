
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 100000
#define POINTS 8
#define REPS 200

static volatile long long sink = 0;


//    1. UNSORTED ARRAY
  /* ============================================================ */
typedef struct {
    int *a;
    int n;
    int cap;
} UArray;

void UA_init(UArray *d, int n) {
    d->cap = n + REPS + 10;
    d->a = malloc((size_t)d->cap * sizeof(int));
    d->n = n;
    /* Reverse order makes search/delete scan behavior easy to observe. */
    for (int i = 0; i < n; ++i) d->a[i] = n - i;
}

void UA_free(UArray *d) { free(d->a); }

int UA_search(UArray *d, int key) {
    for (int i = 0; i < d->n; ++i)
        if (d->a[i] == key) return i;
    return -1;
}

void UA_insert(UArray *d, int key) {
    d->a[d->n++] = key;
}

void UA_delete(UArray *d, int index) {
    if (index < 0 || index >= d->n) return;
    for (int i = index; i < d->n - 1; ++i) d->a[i] = d->a[i + 1];
    --d->n;
}

int UA_max(UArray *d) {
    int p = 0;
    for (int i = 1; i < d->n; ++i)
        if (d->a[i] > d->a[p]) p = i;
    return p;
}

int UA_min(UArray *d) {
    int p = 0;
    for (int i = 1; i < d->n; ++i)
        if (d->a[i] < d->a[p]) p = i;
    return p;
}

int UA_pred(UArray *d, int index) {
    int key = d->a[index], p = -1;
    for (int i = 0; i < d->n; ++i) {
        if (i != index && d->a[i] < key && (p == -1 || d->a[i] > d->a[p])) p = i;
    }
    return p;
}

int UA_succ(UArray *d, int index) {
    int key = d->a[index], p = -1;
    for (int i = 0; i < d->n; ++i) {
        if (i != index && d->a[i] > key && (p == -1 || d->a[i] < d->a[p])) p = i;
    }
    return p;
}

/* ============================================================
   2. SORTED ARRAY
   ============================================================ */
typedef struct {
    int *a;
    int n;
    int cap;
} SArray;

void SA_init(SArray *d, int n) {
    d->cap = n + REPS + 10;
    d->a = malloc((size_t)d->cap * sizeof(int));
    d->n = n;
    for (int i = 0; i < n; ++i) d->a[i] = i + 1;
}

void SA_free(SArray *d) { free(d->a); }

int SA_search(SArray *d, int key) {
    int lo = 0, hi = d->n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (d->a[mid] == key) return mid;
        if (d->a[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

void SA_insert(SArray *d, int key) {
    int i = d->n - 1;
    while (i >= 0 && d->a[i] > key) {
        d->a[i + 1] = d->a[i];
        --i;
    }
    d->a[i + 1] = key;
    ++d->n;
}

void SA_delete(SArray *d, int index) {
    if (index < 0 || index >= d->n) return;
    for (int i = index; i < d->n - 1; ++i) d->a[i] = d->a[i + 1];
    --d->n;
}

int SA_max(SArray *d) { return d->n - 1; }
int SA_min(SArray *d) { (void)d; return 0; }
int SA_pred(SArray *d, int index) { (void)d; return (index > 0) ? index - 1 : -1; }
int SA_succ(SArray *d, int index) { return (index + 1 < d->n) ? index + 1 : -1; }

/* ============================================================
   3. SINGLY LINKED UNSORTED LIST
   ============================================================ */
typedef struct SNode {
    int key;
    struct SNode *next;
} SNode;

typedef struct { SNode *head; } SList;

SNode *new_snode(int key) {
    SNode *p = malloc(sizeof(SNode));
    if (!p) { perror("malloc"); exit(EXIT_FAILURE); }
    p->key = key; p->next = NULL; return p;
}

void SLU_init(SList *d, int n) {
    d->head = NULL;
    for (int i = 1; i <= n; ++i) {
        SNode *p = new_snode(i);
        p->next = d->head;
        d->head = p;
    }
}

void SL_free(SList *d) {
    SNode *p = d->head;
    while (p) { SNode *q = p->next; free(p); p = q; }
    d->head = NULL;
}

SNode *SLU_search(SList *d, int key) {
    for (SNode *p = d->head; p; p = p->next)
        if (p->key == key) return p;
    return NULL;
}

void SLU_insert(SList *d, int key) {
    SNode *p = new_snode(key);
    p->next = d->head;
    d->head = p;
}

void SLU_delete(SList *d, SNode *x) {
    if (!x || !d->head) return;
    if (d->head == x) { d->head = x->next; free(x); return; }
    SNode *p = d->head;
    while (p->next && p->next != x) p = p->next;
    if (p->next == x) { p->next = x->next; free(x); }
}

SNode *SLU_max(SList *d) {
    SNode *best = d->head;
    for (SNode *p = d->head->next; p; p = p->next)
        if (p->key > best->key) best = p;
    return best;
}

SNode *SLU_min(SList *d) {
    SNode *best = d->head;
    for (SNode *p = d->head->next; p; p = p->next)
        if (p->key < best->key) best = p;
    return best;
}

SNode *SLU_pred(SList *d, SNode *x) {
    int key = x->key; SNode *best = NULL;
    for (SNode *p = d->head; p; p = p->next)
        if (p != x && p->key < key && (!best || p->key > best->key)) best = p;
    return best;
}

SNode *SLU_succ(SList *d, SNode *x) {
    int key = x->key; SNode *best = NULL;
    for (SNode *p = d->head; p; p = p->next)
        if (p != x && p->key > key && (!best || p->key < best->key)) best = p;
    return best;
}

/* ============================================================
   4. SINGLY LINKED SORTED LIST
   ============================================================ */
void SLS_init(SList *d, int n) {
    d->head = NULL; SNode **tail = &d->head;
    for (int i = 1; i <= n; ++i) { *tail = new_snode(i); tail = &(*tail)->next; }
}

SNode *SLS_search(SList *d, int key) {
    for (SNode *p = d->head; p && p->key <= key; p = p->next) {
        if (p->key == key) return p;
    }
    return NULL;
}

void SLS_insert(SList *d, int key) {
    SNode *x = new_snode(key);
    if (!d->head || d->head->key > key) { x->next = d->head; d->head = x; return; }
    SNode *p = d->head;
    while (p->next && p->next->key < key) p = p->next;
    x->next = p->next; p->next = x;
}

void SLS_delete(SList *d, SNode *x) {
    if (!x || !d->head) return;
    if (d->head == x) { d->head = x->next; free(x); return; }
    SNode *p = d->head;
    while (p->next && p->next != x) p = p->next;
    if (p->next == x) { p->next = x->next; free(x); }
}

SNode *SLS_max(SList *d) {
    SNode *p = d->head;
    while (p->next) p = p->next;
    return p;
}
SNode *SLS_min(SList *d) { return d->head; }
SNode *SLS_pred(SList *d, SNode *x) {
    SNode *prev = NULL;
    for (SNode *p = d->head; p && p != x; p = p->next) prev = p;
    return prev;
}
SNode *SLS_succ(SList *d, SNode *x) { (void)d; return x ? x->next : NULL; }

/* ============================================================
   5. DOUBLY LINKED UNSORTED LIST
   ============================================================ */
typedef struct DNode {
    int key;
    struct DNode *prev, *next;
} DNode;

typedef struct { DNode *head; } DList;

DNode *new_dnode(int key) {
    DNode *p = malloc(sizeof(DNode));
    if (!p) { perror("malloc"); exit(EXIT_FAILURE); }
    p->key = key; p->prev = p->next = NULL; return p;
}

void DLU_init(DList *d, int n) {
    d->head = NULL;
    for (int i = 1; i <= n; ++i) {
        DNode *p = new_dnode(i);
        p->next = d->head;
        if (d->head) d->head->prev = p;
        d->head = p;
    }
}

void DL_free(DList *d) {
    DNode *p = d->head;
    while (p) { DNode *q = p->next; free(p); p = q; }
    d->head = NULL;
}

DNode *DLU_search(DList *d, int key) {
    for (DNode *p = d->head; p; p = p->next)
        if (p->key == key) return p;
    return NULL;
}

void DLU_insert(DList *d, int key) {
    DNode *p = new_dnode(key);
    p->next = d->head;
    if (d->head) d->head->prev = p;
    d->head = p;
}

void DLU_delete(DList *d, DNode *x) {
    if (!x) return;
    if (x->prev) x->prev->next = x->next;
    else d->head = x->next;
    if (x->next) x->next->prev = x->prev;
    free(x);
}

DNode *DLU_max(DList *d) {
    DNode *best = d->head;
    for (DNode *p = d->head->next; p; p = p->next)
        if (p->key > best->key) best = p;
    return best;
}
DNode *DLU_min(DList *d) {
    DNode *best = d->head;
    for (DNode *p = d->head->next; p; p = p->next)
        if (p->key < best->key) best = p;
    return best;
}
DNode *DLU_pred(DList *d, DNode *x) {
    int key = x->key; DNode *best = NULL;
    for (DNode *p = d->head; p; p = p->next)
        if (p != x && p->key < key && (!best || p->key > best->key)) best = p;
    return best;
}
DNode *DLU_succ(DList *d, DNode *x) {
    int key = x->key; DNode *best = NULL;
    for (DNode *p = d->head; p; p = p->next)
        if (p != x && p->key > key && (!best || p->key < best->key)) best = p;
    return best;
}

/* ============================================================
   6. DOUBLY LINKED SORTED LIST
   ============================================================ */
void DLS_init(DList *d, int n) {
    d->head = NULL; DNode *tail = NULL;
    for (int i = 1; i <= n; ++i) {
        DNode *p = new_dnode(i);
        if (!d->head) d->head = p;
        p->prev = tail;
        if (tail) tail->next = p;
        tail = p;
    }
}

DNode *DLS_search(DList *d, int key) {
    for (DNode *p = d->head; p && p->key <= key; p = p->next)
        if (p->key == key) return p;
    return NULL;
}

void DLS_insert(DList *d, int key) {
    DNode *x = new_dnode(key);
    if (!d->head || d->head->key > key) {
        x->next = d->head;
        if (d->head) d->head->prev = x;
        d->head = x;
        return;
    }
    DNode *p = d->head;
    while (p->next && p->next->key < key) p = p->next;
    x->next = p->next; x->prev = p;
    if (p->next) p->next->prev = x;
    p->next = x;
}

void DLS_delete(DList *d, DNode *x) {
    if (!x) return;
    if (x->prev) x->prev->next = x->next;
    else d->head = x->next;
    if (x->next) x->next->prev = x->prev;
    free(x);
}

DNode *DLS_max(DList *d) {
    DNode *p = d->head;
    while (p->next) p = p->next;
    return p;
}
DNode *DLS_min(DList *d) { return d->head; }
DNode *DLS_pred(DList *d, DNode *x) { (void)d; return x ? x->prev : NULL; }
DNode *DLS_succ(DList *d, DNode *x) { (void)d; return x ? x->next : NULL; }

/* ============================================================
   TIMING HELPERS
   ============================================================ */
static double elapsed(clock_t start, clock_t end) {
    return 1e6 * (double)(end - start) / (double)CLOCKS_PER_SEC;
}

/* Use a batch for timing. For insertion/deletion, the data structure is
   deliberately changed during the batch; this is sufficient for growth
   experiments. The reported value is average microseconds per operation. */

void bench_unsorted_array(int n, FILE *out) {
    UArray d; UA_init(&d, n);
    int target = n + 1; /* absent: full search */
    int xidx = n / 2;
    clock_t s, e;

    s = clock(); for (int r=0;r<REPS;r++) sink += UA_search(&d,target); e=clock(); double search=elapsed(s,e)/REPS;

    s = clock(); for (int r=0;r<REPS;r++) UA_insert(&d, 2*n+r); e=clock(); double ins=elapsed(s,e)/REPS;

    /* Recreate at original size, delete middle item. */
    UA_free(&d); UA_init(&d,n); xidx=n/2;
    s=clock(); for(int r=0;r<REPS;r++){ int idx=(d.n/2); UA_delete(&d,idx); UA_insert(&d,2*n+r); } e=clock(); double del=elapsed(s,e)/REPS;

    UA_free(&d); UA_init(&d,n); xidx=n/2;
    s=clock(); for(int r=0;r<REPS;r++) sink += UA_max(&d); e=clock(); double mx=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += UA_min(&d); e=clock(); double mn=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += UA_pred(&d,xidx); e=clock(); double pr=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += UA_succ(&d,xidx); e=clock(); double su=elapsed(s,e)/REPS;

    fprintf(out,"%d %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n",n,search,ins,del,mx,mn,pr,su);
    UA_free(&d);
}

void bench_sorted_array(int n, FILE *out) {
    SArray d; SA_init(&d,n); int target=n+1, xidx=n/2; clock_t s,e;
    s=clock(); for(int r=0;r<REPS;r++) sink += SA_search(&d,target); e=clock(); double search=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) SA_insert(&d,2*n+r); e=clock(); double ins=elapsed(s,e)/REPS;
    SA_free(&d); SA_init(&d,n); xidx=n/2;
    s=clock(); for(int r=0;r<REPS;r++){ SA_delete(&d,xidx); SA_insert(&d,xidx+1); } e=clock(); double del=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += SA_max(&d); e=clock(); double mx=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += SA_min(&d); e=clock(); double mn=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += SA_pred(&d,xidx); e=clock(); double pr=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += SA_succ(&d,xidx); e=clock(); double su=elapsed(s,e)/REPS;
    fprintf(out,"%d %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n",n,search,ins,del,mx,mn,pr,su); SA_free(&d);
}

void bench_singly_unsorted(int n, FILE *out) {
    SList d; SLU_init(&d,n); int target=n+1; SNode *x=SLU_search(&d,n/2); clock_t s,e;
    s=clock(); for(int r=0;r<REPS;r++) sink += (SLU_search(&d,target)!=NULL); e=clock(); double search=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) SLU_insert(&d,2*n+r); e=clock(); double ins=elapsed(s,e)/REPS;
    SL_free(&d); SLU_init(&d,n); x=SLU_search(&d,n/2);
    s=clock(); for(int r=0;r<REPS;r++){ SNode *z=SLU_search(&d,n/2); SLU_delete(&d,z); SLU_insert(&d,n/2); } e=clock(); double del=elapsed(s,e)/REPS;
    x=SLU_search(&d,n/2);
    s=clock(); for(int r=0;r<REPS;r++) sink += SLU_max(&d)->key; e=clock(); double mx=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += SLU_min(&d)->key; e=clock(); double mn=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (SLU_pred(&d,x)!=NULL); e=clock(); double pr=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (SLU_succ(&d,x)!=NULL); e=clock(); double su=elapsed(s,e)/REPS;
    fprintf(out,"%d %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n",n,search,ins,del,mx,mn,pr,su); SL_free(&d);
}

void bench_singly_sorted(int n, FILE *out) {
    SList d; SLS_init(&d,n); int target=n+1; SNode *x=SLS_search(&d,n/2); clock_t s,e;
    s=clock(); for(int r=0;r<REPS;r++) sink += (SLS_search(&d,target)!=NULL); e=clock(); double search=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) SLS_insert(&d,2*n+r); e=clock(); double ins=elapsed(s,e)/REPS;
    SL_free(&d); SLS_init(&d,n); x=SLS_search(&d,n/2);
    s=clock(); for(int r=0;r<REPS;r++){ SNode *z=SLS_search(&d,n/2); SLS_delete(&d,z); SLS_insert(&d,n/2); } e=clock(); double del=elapsed(s,e)/REPS;
    x=SLS_search(&d,n/2);
    s=clock(); for(int r=0;r<REPS;r++) sink += SLS_max(&d)->key; e=clock(); double mx=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += SLS_min(&d)->key; e=clock(); double mn=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (SLS_pred(&d,x)!=NULL); e=clock(); double pr=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (SLS_succ(&d,x)!=NULL); e=clock(); double su=elapsed(s,e)/REPS;
    fprintf(out,"%d %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n",n,search,ins,del,mx,mn,pr,su); SL_free(&d);
}

void bench_doubly_unsorted(int n, FILE *out) {
    DList d; DLU_init(&d,n); int target=n+1; DNode *x=DLU_search(&d,n/2); clock_t s,e;
    s=clock(); for(int r=0;r<REPS;r++) sink += (DLU_search(&d,target)!=NULL); e=clock(); double search=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) DLU_insert(&d,2*n+r); e=clock(); double ins=elapsed(s,e)/REPS;
    DL_free(&d); DLU_init(&d,n); x=d.head;
    s=clock(); for(int r=0;r<REPS;r++){ DNode *z=d.head; DLU_delete(&d,z); DLU_insert(&d,n/2); } e=clock(); double del=elapsed(s,e)/REPS;
    x=DLU_search(&d,n/2);
    s=clock(); for(int r=0;r<REPS;r++) sink += DLU_max(&d)->key; e=clock(); double mx=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += DLU_min(&d)->key; e=clock(); double mn=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (DLU_pred(&d,x)!=NULL); e=clock(); double pr=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (DLU_succ(&d,x)!=NULL); e=clock(); double su=elapsed(s,e)/REPS;
    fprintf(out,"%d %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n",n,search,ins,del,mx,mn,pr,su); DL_free(&d);
}

void bench_doubly_sorted(int n, FILE *out) {
    DList d; DLS_init(&d,n); int target=n+1; DNode *x=DLS_search(&d,n/2); clock_t s,e;
    s=clock(); for(int r=0;r<REPS;r++) sink += (DLS_search(&d,target)!=NULL); e=clock(); double search=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) DLS_insert(&d,2*n+r); e=clock(); double ins=elapsed(s,e)/REPS;
    DL_free(&d); DLS_init(&d,n); x=d.head;
    s=clock(); for(int r=0;r<REPS;r++){ DNode *z=d.head; DLS_delete(&d,z); DLS_insert(&d,n/2); } e=clock(); double del=elapsed(s,e)/REPS;
    x=DLS_search(&d,n/2);
    s=clock(); for(int r=0;r<REPS;r++) sink += DLS_max(&d)->key; e=clock(); double mx=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += DLS_min(&d)->key; e=clock(); double mn=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (DLS_pred(&d,x)!=NULL); e=clock(); double pr=elapsed(s,e)/REPS;
    s=clock(); for(int r=0;r<REPS;r++) sink += (DLS_succ(&d,x)!=NULL); e=clock(); double su=elapsed(s,e)/REPS;
    fprintf(out,"%d %.6f %.6f %.6f %.6f %.6f %.6f %.6f\n",n,search,ins,del,mx,mn,pr,su); DL_free(&d);
}

void make_file(const char *filename, void (*bench)(int, FILE *)) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror(filename); exit(EXIT_FAILURE); }
    fprintf(f, "# n search insert delete max min predecessor successor\n");
    int sizes[POINTS] = {100, 500, 1000, 5000, 10000, 25000, 50000, 75000};
    for (int i=0; i<POINTS; ++i) {
        printf("  n = %d\n", sizes[i]);
        bench(sizes[i], f);
    }
    fclose(f);
}

int main(void) {
    printf("Generating GNUplot data...\n");
    make_file("unsorted_array.dat", bench_unsorted_array);
    make_file("sorted_array.dat", bench_sorted_array);
    make_file("singly_unsorted.dat", bench_singly_unsorted);
    make_file("singly_sorted.dat", bench_singly_sorted);
    make_file("doubly_unsorted.dat", bench_doubly_unsorted);
    make_file("doubly_sorted.dat", bench_doubly_sorted);
    printf("Done. sink=%lld\n", sink);
    return 0;
}
