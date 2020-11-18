#include<stdio.h>

#define rep(i,n) for(i=0;i<n;i++)
#define MAX 200003

int main(void){
    
    int i, n, w;
    long long need[MAX], sum=0;

    rep(i, MAX) need[i] = 0; 

    scanf("%d %d", &n, &w);
    rep(i, n){
        int s, t, p;
        scanf("%d %d %d", &s, &t, &p);
        need[s] += p;
        need[t] += -p;
    }

    rep(i, MAX){
        sum+=need[i];
        if( sum>w ){ printf("No\n"); return 0; }
    }

    printf("Yes\n");
    return 0;
}
