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

int merge(int x, int y){ return x^y; }
segTree* segTreeInit(int n){
    int i, N=1;
    segTree *st;
    while( N<n ) N*=2;

    st = (segTree*)malloc(sizeof(segTree));
    if( st ){
        int **tree=&(st->tree);
        st->N = N;
        *tree = (int*)malloc((2*N-1)*sizeof(int));
        if( *tree ){
            rep(i, 2*N-1) (*tree)[i]=0;
            rep(i, n) scanf("%d", &((*tree)[i+N-1]));
            for(i=N-2;i>=0;i--){
                int lc, rc;
                lc = childL(i); rc=childR(i);
                (*tree)[i] = merge((*tree)[lc], (*tree)[rc]);
            }
        }
    }
    return st;
}

void update(segTree *st, int idx, int x){
    //printf("idx=%d, x=%d\n", idx, x);
    int *tree, N;
    tree = st->tree; N=st->N;
    idx += (N-1);

    tree[idx] = x;
    while( idx>0 ){
        idx = parent(idx);
        int lc=childL(idx), rc=childR(idx);
        tree[idx] = merge(tree[lc], tree[rc]);
    }
    tree[0] = merge(tree[1], tree[2]);
}

int getValue(int *tree, int sl, int sr, int idx, int cl, int cr){
    //printf("sl=%d, sr=%d\n", sl, sr);
    //printf("idx=%d, cl=%d, cr=%d\n", idx, cl, cr);
    if( cr<=sl || sr<=cl ) return 0;
    if( sl<=cl && cr<=sr ) return tree[idx];

    int lv, rv, mid=(cl+cr)/2;
    lv = getValue(tree, sl, sr, childL(idx), cl, mid);
    rv = getValue(tree, sl, sr, childR(idx), mid, cr);
    return merge(lv, rv);
}

int main(void){
    
    int i, j;
    int n, q, N, *tree;
    segTree *segtree;
    scanf("%d %d", &n, &q);
    segtree = segTreeInit(n);

    N = segtree->N;
    tree = segtree->tree;

    //printf("N=%d\n", N);
    //rep(i, 2*N-1) printf("%d ", tree[i]);

    rep(j, q){
        int t, x, y;
        scanf("%d %d %d", &t, &x, &y);
        if( t==1 ){
            update(segtree, x-1, tree[N+x-2]^y);
            //printf("N=%d\n", N);
            //rep(i, 2*N-1) printf("%d ", tree[i]);
        }
        else{
            int ans;
            ans = getValue(segtree->tree, x-1, y, 0, 0, segtree->N);
            printf("%d\n", ans);
        }
    }
    return 0;
}
