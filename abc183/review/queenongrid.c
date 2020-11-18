#include<stdio.h>

#define rep(i,n) for(i=0;i<n;i++)
#define MOD 1000000007
#define MAX 2002

int main(void){
    
    int i, j, h, w, dp;
    int ex[2][MAX], ey[2][MAX], exy[2][MAX]; 
    char str[MAX][MAX];
    
    scanf("%d %d", &h, &w);

    rep( i, h) scanf("%s", str[i]);

    for(i=0; i<h; i++){
        int cur=i%2, pre=cur^1;
        rep( j, w){
            ex[cur][j] = 0;
            ey[cur][j] = 0;
            exy[cur][j] = 0;
        }
        // +---------------------------------------------------------------------+
        // |  dp[i][j]                                ex[i][j]                   |
        // |  =ex[i][j-1]+ey[i-1][j]+exy[i-1][j-1]    =ex[i][j-1]+dp[i][j-1]     |
        // |                                                                     |
        // |  ey[i][j]                                exy[i][j]                  |
        // |  =ey[i-1][j]+dp[i-1][j]                  =exy[i-1][j-1]+dp[i-1][j-1]|
        // +---------------------------------------------------------------------+
        rep(j, w){
            if( str[i][j]=='#' ) continue;
            if( i==0 && j==0 ){
                dp=1;
                ex[0][0] = 1 ;
                ey[0][0] = 1 ;
                exy[0][0] = 1 ;
                continue;
            }
            if( j>0 )    ex[cur][j] = ex[cur][j-1];
            if( i>0 )    ey[cur][j] = ey[pre][j];
            if(i>0&&j>0) exy[cur][j] = exy[pre][j-1];
            
            dp = ( (ex[cur][j] + ey[cur][j])%MOD + exy[cur][j] )%MOD;
            
            ex[cur][j] = (dp+ex[cur][j]) %MOD;
            ey[cur][j] = (dp+ey[cur][j]) %MOD;
            exy[cur][j] = (dp+ exy[cur][j]) %MOD;
        }
    }
    
    printf("%d\n", dp);
    
    return 0;
}
