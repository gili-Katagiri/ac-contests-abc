#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

int main(void){

    int nn, n, m, t, i, c=0;

    scanf("%d", &nn);
    scanf("%d", &m);
    scanf("%d", &t);
    
    n = nn;
    rep(i, m){
        int a, b;
        scanf("%d", &a);
        scanf("%d", &b);
        //printf("now: %d\n", n);
        n -= (a-c);
        //printf("arrive: %d\n", n);
        if( n<=0 ) break;
        else{ n+=(b-a); c=b; }
        if( n>nn ) n=nn;
        //printf("leave: %d\n", n);
    }
    n -= (t-c);
    //printf("result: %d\n", n);
    if( n<=0 ) printf("No\n");
    else printf("Yes\n");

    return 0;

}
