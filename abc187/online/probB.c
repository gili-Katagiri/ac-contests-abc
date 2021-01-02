#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)
#define MAX 1005

int main(void) {

    int i, j, n, cnt=0;
    int x[MAX], y[MAX];

    scanf("%d", &n);

    rep(i, n){
        scanf("%d %d", &x[i], &y[i]);
        rep(j, i){
            double slope;
            slope = (double)( y[j] - y[i] ) / ( x[j] - x[i] );
            if( slope >= -1 && slope<=1 ) {
                cnt++;
            }
        }
    }

    printf("%d\n", cnt);

    return 0;

}
