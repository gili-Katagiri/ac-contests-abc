#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

int main(void) {

    int i, n;
    int *a, *b;

    scanf("%d", &n);
    a = (int*)malloc(n*sizeof(int));
    b = (int*)malloc(n*sizeof(int));
    rep(i, n){
        scanf("%d %d", &a[i], &b[i]);
    }

    printf("%d\n", x);

    return 0;

}
