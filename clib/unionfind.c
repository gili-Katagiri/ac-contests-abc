#include<stdio.h>
#include<stdlib.h>
#define rep(i,n) for(i=0;i<n;i++)

// ================================================================================
// if p[x]==y: x and y is the same group,
// if p[x]<0: x is the leader of group and (-p[x]) express as group size.
void intSwap(int*, int*);
int* ufInit(int);
int ufRoot(int, int*);
char ufUnite(int*, int*, int*);
// --------------------------------------------------------------------------------
int main(void){
    int i, n=10;
    int *p;
    p=ufInit(n);

    for(i=0;i<n;i++){
        int s, t, sp, tp;
        s=(i*i+2)%n; t=(s*s+1)%n;
        sp=s; tp=t;
        ufUnite(&s, &t, p);
        printf("Unite: %d(%d) and %d(%d)\n", s, sp, t, tp);
    }
    printf("result: ");
    rep(i, n) printf("%d ", p[i]);
    putchar('\n');

    return 0;
}

// --------------------------------------------------------------------------------
void intSwap(int *x, int *y){
    int tmp=*x;
    *x=*y;
    *y=tmp;
}
int* ufInit(int n){
    int i;
    int *p;
    p = (int*)malloc(n*sizeof(int));
    rep(i, n){ p[i]=-1; }
    return p;
}
int ufRoot(int x, int *p){
    if( p[x]<0 ){ return x; }
    else{ return ( p[x] = ufRoot(p[x], p) ); }
}
char ufUnite(int *x, int *y, int *p){
    *x=ufRoot(*x, p), *y=ufRoot(*y, p);
    if( *x==*y ) return 0; // none process
    // make size(x) smaller than size(y)
    // x, y: leader of group, p[x]<p[y] => size(x)>size(y)
    if( p[*x]<p[*y] ) intSwap(x, y);
    // merge x to y
    p[*y] += p[*x]; // size merge
    p[*x] = *y;
    return 1;
}
// ================================================================================
