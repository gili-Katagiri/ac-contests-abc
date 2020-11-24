#include<stdio.h>

#define rep(i, n) for(i=0;i<n;i++)

int main(void){
    int a, b, c;
    int i, j, k;
    double e[100][100][100];

    scanf("%d %d %d", &a, &b, &c);

    e[0][0][0] = 1;
    rep(i, 100) rep(j, 100) rep(k, 100){
        if( i==0 && j==0 && k==0 ) continue;
        int ri, rj, rk;
        ri=99-i; rj=99-j; rk=99-k;
        int sum=ri+rj+rk;
        double esum=1;
        if( i>0 ) esum+=( e[i-1][j][k]*(ri)/sum );
        if( j>0 ) esum+=( e[i][j-1][k]*(rj)/sum );
        if( k>0 ) esum+=( e[i][j][k-1]*(rk)/sum );
        e[i][j][k] = esum;
    }
    

    printf("%f\n", e[99-a][99-b][99-c]);

    return 0;

}
