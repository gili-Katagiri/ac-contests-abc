#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

long long comb(int s, int t){
    // sCt
    int i, d;
    long long ans=1;
    d = s-t>t?t:s-t;
    //printf("d: %d\n", d); 
    rep(i, d){
        ans *= (s-i);
        ans /= (i+1);
    }
    return ans;
}
int main(void){

    int l;
    long long ans;

    scanf("%d", &l);

    ans = comb(l-1, 11);

    printf("%lld\n", ans);

    return 0;

}
