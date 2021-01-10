#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

int childL(int i){ return 2*i+1; }
int childR(int i){ return 2*i+2; }
int parent(int i){ return (i-1)/2; }

typedef struct SegmentTree{
    int N; // N=2**k | min(k|2**k>=n)  
    int *tree;
}segTree;

int merge(int x, int y){ return x>y?x:y; }

segTree* segTreeInit(int n){
    int i, N;
    segTree *st;

    N = (1<<n);

    st = (segTree*)malloc(sizeof(segTree));
    if( st ){
        int **tree=&(st->tree);
        st->N = N;
        *tree = (int*)malloc((2*N-1)*sizeof(int));
        if( *tree ){
            rep(i, N) scanf("%d", &((*tree)[i+N-1]));
            for(i=N-2;i>=0;i--){
                int lc, rc;
                lc = childL(i); rc=childR(i);
                (*tree)[i] = merge((*tree)[lc], (*tree)[rc]);
            }
        }
    }
    return st;
}


int main(void) {

    int i, n, N, ans_rate, idx;
    int **tree;
    segTree *segtree;

    scanf("%d", &n);
    N = (1<<n);
    segtree = segTreeInit(n);
    tree = &(segtree->tree);
    
    //rep(i, (2<<n)-1) printf("%d ", (*tree)[i]);
    //putchar('\n');

    
    ans_rate = (*tree)[1]>(*tree)[2]?(*tree)[2]:(*tree)[1];
    idx = -1;
    rep(i, 1<<n){
        if( ans_rate == (*tree)[N-1+i] ){
            idx = i;
            break;
        }else{
            continue;
        }
    }

    printf("%d\n", idx+1);

    return 0;

}
