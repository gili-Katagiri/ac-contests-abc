#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

int main(void) {

    int a, b, sa=0, sb=0;

    scanf("%d %d", &a, &b);
    
    while( a!=0 ){
        sa += a%10;
        a /= 10;
    }
    while( b!=0 ){
        sb += b%10;
        b /= 10;
    }
    
    if( sa>sb ){
        printf("%d\n", sa);
    }else{
        printf("%d\n", sb);
    }
    return 0;

}
