#include<stdio.h>


void inputArr(int arr1[],int arr2[],int n){

    printf("enter the sorted set1; ");
    for(int i=0;i<n;i++){
        scanf("%d",&arr1[i]);
    }
    printf("enter the sorted set2; ");
    for(int i=0;i<n;i++){
        scanf("%d",&arr2[i]);
    }
}


int binarySearch(int arr2[], int k,int n){
    int l=0, r= n-1;
    while(l<r){
        int mid = l+(r-l)/2;
        if(arr2[mid]==k){
            return mid;
        }
        else if(arr2[mid]>k){
            r= mid-1;
        }
        else{
            l = mid+1;
        }
    }
    return -1;
}


int main(){
    int n,x;
    printf("enter the size of sets ");
    scanf("%d",&n);

    int arr1[n], arr2[n];
    inputArr(arr1,arr2,n);

    printf("enter the key; ");
    scanf("%d",&x);
    int found =0;
    for(int i=0;i<n;i++){
        int req =x- arr1[i];
        int index=binarySearch(arr2,req,n);
        
        if(index!=-1){
            printf("%d from S1 + %d from S2 = %d\n",arr1[i], arr2[index], x);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nNo such pair exists.\n");}
    return 0;
}