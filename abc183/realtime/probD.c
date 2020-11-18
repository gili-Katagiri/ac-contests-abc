#include<stdio.h>

#define rep(i,n) for(i=0;i<n;i++)
#define MAX 200003

int main(void){
    
    int i, n;
    unsigned long long need[MAX], w, m=0;

    rep(i, MAX) need[i] = 0; 

    scanf("%d %lld", &n, &w);
    rep(i, n){
        int j, s, t, p;
        scanf("%d %d %d", &s, &t, &p);

        for(j=s; j<t; j++){
            need[j] += p;
            if( m<need[j] ) m=need[j];
        }
    }
    
    if( m<=w ) printf("Yes\n");
    else printf("No\n");

    return 0;
}
