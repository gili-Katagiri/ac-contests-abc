#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

int compareInt(const void* a, const void* b){
    int aNum, bNum;
    aNum = *(int*)a;
    bNum = *(int*)b;
    return aNum-bNum;
}
int main(void) {

    int i, j, n, C, lim=-1;
    int *a, *b, *c, *d;

    scanf("%d %d", &n, &C);
    a = (int*)malloc(n*sizeof(int));
    b = (int*)malloc(n*sizeof(int));
    c = (int*)malloc(n*sizeof(int));
    d = (int*)malloc(2*n*sizeof(int));

    rep(i, n){
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
        a[i] -= 1;
        d[2*i] = a[i];
        d[2*i+1] = b[i];
    }
    qsort(d, 2*n, sizeof(int), compareInt);

    long long price, total;
    price = 0;
    total = 0;
    for(i=0; i<2*n-1; i++){
        int diff;
        diff = d[i+1] - d[i];
        rep(j, n){
            if( d[i]==a[j] ) price+=c[j];
            if( d[i]==b[j] ) price-=c[j];
        }
        total += ( (C>price?price:C) * diff ); 
    }

    printf("%lld\n", total);

    return 0;

}
