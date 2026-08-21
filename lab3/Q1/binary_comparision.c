#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// ---------- Binary Search ----------
int binarySearch(int arr[], int l, int r, int search){
    while(l <= r){
        int mid = l + (r-l)/2;
        if(arr[mid] == search){
            return mid;
        }
        if(arr[mid] < search){
            l = mid+1;
        }
        else{
            r = mid-1;
        }
    }
    return -1;
}

// ---------- Ternary Search ----------
int ternarySearch(int arr[], int l, int r, int search){
    while(l <= r){
        int mid1 = l + (r-l)/3;
        int mid2 = r - (r-l)/3;

        if(arr[mid1] == search) return mid1;
        if(arr[mid2] == search) return mid2;

        if(search < arr[mid1]){
            r = mid1 - 1;
        }
        else if(search > arr[mid2]){
            l = mid2 + 1;
        }
        else{
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }
    return -1;
}

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    // input sizes to test
    int sizes[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000,
                   5000000, 10000000, 50000000};
    int numSizes = sizeof(sizes)/sizeof(sizes[0]);

    int trials = 2000; 

    FILE *fp = fopen("timing_data.txt", "w");
    if(fp == NULL){
        printf("Error opening file\n");
        return 1;
    }

    fprintf(fp, "# n\tbinary_time(us)\tternary_time(us)\n");

    srand(time(NULL));

    for(int s = 0; s < numSizes; s++){
        int n = sizes[s];
        int *arr = malloc(n * sizeof(int));

        for(int i = 0; i < n; i++){
            arr[i] = i * 2; // sorted array: 0,2,4,6,...
        }

        int *targets = malloc(trials * sizeof(int));
        for(int i = 0; i < trials; i++){
            if(i % 2 == 0)
                targets[i] = arr[rand() % n];        // guaranteed present
            else
                targets[i] = (rand() % n) * 2 + 1;    // guaranteed absent (odd)
        }

   
        volatile int sink = 0;

        // ---- time binary search ----
        clock_t start = clock();
        for(int i = 0; i < trials; i++){
            sink += binarySearch(arr, 0, n-1, targets[i]);
        }
        clock_t end = clock();
        double binTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1e6 / trials; // microseconds per search

        // ---- time ternary search ----
        start = clock();
        for(int i = 0; i < trials; i++){
            sink += ternarySearch(arr, 0, n-1, targets[i]);
        }
        end = clock();
        double terTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1e6 / trials;

        printf("n = %10d | binary = %10.4f us | ternary = %10.4f us\n", n, binTime, terTime);
        fprintf(fp, "%d\t%.6f\t%.6f\n", n, binTime, terTime);

        free(arr);
        free(targets);
    }

    fclose(fp);
    printf("\nData written to timing_data.txt\n");
    return 0;
}