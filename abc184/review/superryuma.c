#include<stdio.h>

#define rep(i, n) for(i=0;i<n;i++)

int abs(int x){ return x>=0?x:-x; }

int main(void){
    int a, b, c, d;
    int ans=0;

    scanf("%d", &a); scanf("%d", &b);
    scanf("%d", &c); scanf("%d", &d);

    c=abs(c-a); d=abs(d-b);

    if( c==0 && d==0 ) ans=0;
    else if( c+d<=3 || c==d ) ans=1;
    else if( c+d<=6 ) ans=2;
    else{
        c=c-d; d=0; 
        if( abs(c)<=3 || c%2==0 ) ans=2;
        else ans=3;
    }

    printf("%d\n", ans);

    return 0;

}
