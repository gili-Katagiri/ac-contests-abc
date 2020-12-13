#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

int min(int a, int b, int c){
    int tmp=a;
    if( tmp>b ) tmp=b;
    if( tmp>c ) tmp=c;
    return tmp;
}

int main(void){

    int i, j, n, m, *a, *b;
    int **dp;
    scanf("%d %d", &n, &m);

    a = (int*)malloc(n*sizeof(int));
    b = (int*)malloc(m*sizeof(int));
    rep(i, n) scanf("%d", &a[i]);
    rep(j, m) scanf("%d", &b[j]);
    
    dp = (int**)malloc((n+1)*sizeof(int*));
    rep(i, n+1) dp[i] = (int*)malloc((m+1)*sizeof(int));
    
    dp[0][0] = 0;
    rep(i, n) dp[i+1][0]=i+1;
    rep(j, m) dp[0][j+1]=j+1;
    
    rep(i, n){
        rep(j, m){
            //printf("%d %d\n", i, j);
            int di=i+1, dj=j+1, co;
            co = (a[i]==b[i]?0:1);

            dp[di][dj] = min(
                dp[i][dj]+1,
                dp[di][j]+1,
                dp[i][j]+co
            );
        }
    }

    printf("%d\n", dp[n][m]);

    return 0;

}
