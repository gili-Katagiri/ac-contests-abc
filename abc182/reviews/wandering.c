#include<stdio.h>
#define NMAX 200000

int main(void){
    int i, n, a[NMAX];
    long long serialp=0, ans=0, sectsum=0, sectmax=0;

    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &a[i]);

        sectsum += a[i];

        if( sectsum>sectmax ) sectmax = sectsum;

        if( serialp+sectmax > ans ) ans=serialp+sectmax; 

        serialp = serialp+sectsum;

    }

    printf("%lld", ans);

    return 0;
}

