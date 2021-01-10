#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

int main(void) {
    int i, n;
    int *a, *b;
    long long sum=0;

    scanf("%d", &n);
    a = (int*)malloc(sizeof(int)*n);
    b = (int*)malloc(sizeof(int)*n);

    rep( i, n) scanf("%d", &a[i]);
    rep( i, n) scanf("%d", &b[i]);
    
    rep( i, n){
        sum += (a[i]*b[i]);
    }

    if( sum==0 ) printf("Yes\n");
    else printf("No\n");

    return 0;

}
