#include<stdio.h>
#define NMAX 200000

int main(void){
    int i, n, a[NMAX];
    long long lastp=0, max=0, puresum=0, puremax=0;

    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &a[i]);

        puresum += a[i];
        if( puresum>puremax ){
            puremax = puresum;
        }
        //printf("%lld %lld ", puresum, puremax);

        if( lastp+puremax>max ){ max=lastp+puremax; }
        lastp = lastp+puresum;
        //printf("%lld %lld\n", max, lastp);

    }

    printf("%lld\n", max);

    return 0;
}

