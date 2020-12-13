#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

int main(void){

    int i, n=4, x, min=101;

    rep(i, n){
        scanf("%d", &x);
        if( min>x ) min = x;
    }
    
    printf("%d\n", min);

    return 0;

}
