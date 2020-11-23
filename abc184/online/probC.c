#include<stdio.h>

#define rep(i, n) for(i=0;i<n;i++)

int abs(int x){ return x>=0?x:-x; }

int main(void){
    int a, b, c, d;
    int ans=0;

    scanf("%d", &a); scanf("%d", &b);
    scanf("%d", &c); scanf("%d", &d);

    c=abs(c-a); d=abs(d-b);
    if(c==0 && d==0){ printf("0\n"); return 0; }
    else if( c==0 || d==0 ){
        if( c<=3 && d<=3 ){ printf("1\n"); return 0; }
        else if( c%2==0 && d%2==0 ){ printf("2\n"); }
        else{ printf("3\n"); return 0; }
    } 

    c = abs(c-d); d=0;
    if(c==0){ ans=1; }
    else if( c<=3 ){ ans=2; }
    else if( c%2==0 ){ ans=2; }
    else { ans=3; }

    printf("%d\n", ans);

    return 0;

}
