#include<stdio.h>
#define rep(i, n) for(int i=0; i<n; i++)
#define INF 1010101


int main(void){
    long long n;
    int res[3]={0,0,0}, sum=0, size=0, ans=INF;

    scanf("%lld", &n);
    
    while(n!=0){
        int k;

        k = (n%10)%3;

        sum += k;
        res[k]++;

        n/=10;
        size++;
    }

    rep(i1, 3) rep(i2, 3){

        int sumx, d=i1+i2;

        if( i1>res[1] || i2>res[2] ) break;
        if( d==size || d>2 || d>ans ) break;

        sumx = sum - (i1*1 + i2*2);

        if( sumx%3==0 && ans>d ) ans=d;
    }

    if( ans==INF ) ans=-1;

    printf("%d", ans);

    return 0;
}

