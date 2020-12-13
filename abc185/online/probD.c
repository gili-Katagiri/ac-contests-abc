#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

int main(void){

    int i, n, m, *a;

    scanf("%d", &n);
    scanf("%d", &m);
    a = (int*)malloc(n*sizeof(int));
    rep(i, m) scanf("%d", &a[i]);

    printf("%d\n", n-m);

    return 0;

}
