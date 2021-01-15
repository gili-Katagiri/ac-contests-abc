#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

typedef unsigned int ui;
typedef long long ll;

int compare_ui(const void *a, const void *b){
    ll dval;
    dval = (ll)(*(ui*)b) - (ll)(*(ui*)a);
    if( dval>0 ) return 1;
    else if( dval==0 ) return 0;
    else return -1;
}

int main(void){
    
    int i, n;
    ui *c;
    ll diff=0;

    scanf("%d", &n);
    c = (ui*)malloc(n*sizeof(ui));
    rep(i, n){
        ui a, b;
        scanf("%d %d", &a, &b);
        diff = diff - (ll)a;
        c[i] = 2*a + b;
    }

    qsort(c, n, sizeof(ui), compare_ui);
    //rep(i, n) printf("%u ", c[i]);
    //putchar('\n');

    rep(i, n){
        if( diff>0 ) break;
        diff = diff + (ll)c[i];
    }
    printf("%d\n", i);

    return 0;
}
