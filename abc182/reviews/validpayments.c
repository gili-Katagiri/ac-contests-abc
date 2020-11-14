#include<stdio.h>
#define rep(i, n) for(i=0;i<n;i++)

#define NMAX 53
#define INF 1e17

int debug=0;

int main(void){

    int i, n;
    long long X, a[NMAX], d[NMAX], lim[NMAX];
    long long dp[NMAX][2];

    scanf("%d %lld", &n ,&X);
    rep(i, n) scanf("%lld", &a[i]);
    
    // a[n]=c*a[n-1], d[n-1][1]=d[n-1][0]-a[n]
    //a[n] = 2*a[n-1];
    //while( X>=a[n] ) a[n]+=a[n-1];
    // no available
    a[i]=INF;
    lim[n] = 0;

    d[n] = X;
    for(i=n-1; i>=0; i--){
        d[i] = d[i+1] % a[i+1];
        lim[i] = a[i+1]/a[i];
    }
    lim[n-1] = INF;

    if( debug ){
        for(i=n-1; i>=0; i--){
            int j;
            printf("remain: %3lld, avail: [", d[i]);
            rep( j, i+1){ printf(" %3lld(%2lld)", a[j], lim[j]-1); }
            printf("]\n");
        }
    }
    
    rep(i, n){

        long long di0, di1;
        di0=d[i]; di1=d[i]-a[i+1];
        // dp[i][0]
        
        // d[i]<a[i+1]=a[i]*lim[i] => d[i]/a[i] < lim[i]
        if( di0%a[i]==0 ) dp[i][0] = 1; // i==0: a[0]=1
        else{
            // using a[i]: number of di0/a[i] (<lim[i])
            dp[i][0] = dp[i-1][0];
            // di0 = a[i]*p + q, p<lim[i], q<a[i]
            // if p+1>=lim[i] --> couldn't add dp[i][1]
            if( di0/a[i]+1<lim[i] ) dp[i][0] += dp[i-1][1];
        }

        if( -di1%a[i]==0 ) dp[i][1] = 1; // i==0: a[0]=1
        else{
            dp[i][1] = dp[i-1][1];
            // -di1 = a[i]*p + q, p<lim[i]
            // if p+1>=lim[i] => couldn't add dp[i][1]
            if( (-di1)/a[i]+1<lim[i] ) dp[i][1] += dp[i-1][0];
        }

        if( debug ){
            printf("\nd[i][0]=%lld, dp[i][0]=%lld\n", di0, dp[i][0]);
            printf("d[i][1]=%lld, dp[i][1]=%lld\n\n", di1, dp[i][1]);
        }

    }

    printf("%lld\n", dp[n-1][0]);

    return 0;
}

