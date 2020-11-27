#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)
// permutation iterator ===========================================================
typedef struct PermutationIterator{
    int *perm;
    int *next_swap_point;
    int size;
} permitr;
void arraySwap(int[], int, int);
void partialInsert(int[], int, int);
permitr* permInit(int);
int next_permutation(permitr*);
// --------------------------------------------------------------------------------
int main(void){
    int *permutate, i, n=4;
    permitr *pp;

    //scanf("%d", &n);
    pp = permInit(n); permutate=pp->perm;
    
    do{
        rep(i, n) printf("%d ", permutate[i]);
        putchar('\n');
    }while( next_permutation(pp) );

    return 0;
}
// --------------------------------------------------------------------------------
void arraySwap(int a[], int i, int j){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
void partialInsert(int a[], int f, int t){
    int i, tmp=a[f];
    for(i=f;i<t;i++) a[i]=a[i+1];
    a[t] = tmp;
}
permitr* permInit(int n){
    int i;
    permitr *piptr;
    piptr = (permitr*)malloc(sizeof(permitr));
    if( piptr ){
        piptr->perm=(int*)malloc((n+1)*sizeof(int));
        piptr->next_swap_point=(int*)malloc(n*sizeof(int));
        piptr->size=n;
        rep(i, n){ piptr->perm[i]=i; piptr->next_swap_point[i]=1; }
        piptr->perm[n]=n; // sentinel
    }
    return piptr;
}
int next_permutation(permitr *piptr){
    int *perm, *nsp, size, tp;
    perm=piptr->perm; nsp=piptr->next_swap_point; size=piptr->size;
    for( tp=size-2; tp>=0; tp--){ // n>1, tp: target point
        
        // is [ perm[tp+1], ... ] dict-order?
        if( perm[tp+1]<perm[tp+2] ){ // tp=n-2: true anytime caused sentinel exists
            int sp=tp+nsp[tp];
            if( sp<size ){ // swap update
                arraySwap( perm, tp, sp);
                nsp[tp]++; // next swap point
                return 1;
            }else{ // partialInsert: [3,*2, 0, 1]-> [3, 0, 1,*2]
                partialInsert(perm, tp, size-1);
                nsp[tp]=1;
                continue;
            }
        }

    }
    // exists next perm
    return 0;
}
// ================================================================================
