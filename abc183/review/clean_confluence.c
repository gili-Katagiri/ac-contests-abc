#include<stdio.h>
#include<stdlib.h>
#define rep(i,n) for(i=0;i<n;i++)

// Union Find Tree===========================================================
// if p[x]==y: x and y is the same group,
// if p[x]<0: x is the leader of group and (-p[x]) express as group size.
int *p;
void swap(int*, int*);
void union_find_tree_init(int);
int find(int);
char unite(int*, int*);
// --------------------------------------------------------------------------
// ======================================================================
typedef int MapValue;
typedef struct OrderedIntMap{
    int key;
    MapValue val;
    struct OrderedIntMap *next;
} Map;
Map *MapInit(int, MapValue, Map*);
MapValue *MapKeyValue(Map*, int);
void PrintMap(Map*);
void MapChainInsert(Map**, Map**);
void MapMerge(Map**, Map**);
// ----------------------------------------------------------------------

// Extend uft
Map **map; // map[group][class] = num of classmates the same group
void init_ex(int n, int c[]){
    int i;
    union_find_tree_init(n);
    map = (Map**)malloc(n*sizeof(Map*));
    rep(i, n) map[i]=MapInit(c[i], 1, NULL);
}
void unite_ex(int x, int y){
    char flag;
    flag = unite( &x, &y);
    if( !flag ) return;
    MapMerge(&(map[y]), &(map[x]));
}

int main(void){
    int i, n, q;
    int *c;
    
    scanf("%d %d", &n, &q);
    c = (int*)malloc(n*sizeof(int));
    rep(i, n) scanf("%d", &c[i]); 

    init_ex(n, c);
    free(c);
    
    rep(i, q){
        int t, a, b;
        scanf("%d %d %d", &t, &a, &b);
        if( t==1 ){
            a--; b--;
            unite_ex(a, b);
        }else{
            a = find(a-1);
            int *ans=MapKeyValue(map[a], b);
            if( ans!=NULL ) printf("%d\n", *ans);
            else printf("0\n");
        }
    }
    
    return 0;
}

// ----------------------------------------------------------------------
Map *MapInit(int key, MapValue val, Map *next){
    Map *mptr;
    mptr = (Map*)malloc(sizeof(Map));
    if( mptr ){
        mptr->key = key;
        mptr->val = val;
        mptr->next = next;
    }
    return mptr;
}
MapValue *MapKeyValue(Map *mptr, int key){
    for(; mptr!=NULL && mptr->key<=key; mptr=mptr->next){
        if( mptr->key==key ) return &(mptr->val);
    }
    return NULL;
}
void PrintMap(Map *mptr){
    if( mptr== NULL ){ printf("NULL\n"); return; }
    printf("%p  ", mptr); 
    printf("{ %d: %d", mptr->key, mptr->val);
    for(mptr=mptr->next; mptr!=NULL; mptr=mptr->next){
        printf(", %d: %d", mptr->key, mptr->val);
    }
    printf(" }\n");
}
void MapChainInsert(Map **x, Map **y){
    Map *t=(*x)->next;
    (*x)->next = *y;
    
    if( t==NULL ){ *y=NULL; return; }
    if( (*y)->next==NULL ){ (*y)->next=t; *y=NULL; return; }

    int tkey=t->key;
    while( (*y)->next!=NULL && ((*y)->next)->key<=tkey ) *y=(*y)->next;
    *x = *y;
    *y = (*y)->next;
    if( t->key==(*x)->key ){
        (*x)->val+=t->val;
        (*x)->next=(t->next);
        free(t);
    }else{
        (*x)->next = t;
        *x = t;
    }
}
void MapMerge(Map **xmap, Map **ymap){
    Map *t;
    if( *ymap==NULL ) return;
    else if( (*ymap)->key < (*xmap)->key ){
        t=(*ymap)->next;
        (*ymap)->next = (*xmap);
        *xmap = *ymap;
        *ymap = t;
    }else if( (*xmap)->key==(*ymap)->key ){
        t=(*ymap);
        *ymap=(*ymap)->next;
        (*xmap)->val += t->val;
        free(t);
    }

    // xkey < ykey
    Map *x;
    x = *xmap;
    while( (*ymap)!=NULL ){
        int ykey=(*ymap)->key;
        if( x->next==NULL ){ x->next = (*ymap); *ymap=NULL; return; }

        // make xkey <= ykey < nxkey
        while( x->next!=NULL && (x->next)->key<=ykey ) x=x->next;
        if( x->key == ykey ){
            t=*ymap;
            *ymap = (*ymap)->next;
            x->val += t->val;
            free(t);
            continue;
        } 
        MapChainInsert(&x, ymap);
    }
}
// ======================================================================

// --------------------------------------------------------------------------
void swap(int *x, int *y){
    int tmp=*x;
    *x=*y;
    *y=tmp;
}
void union_find_tree_init(int n){
    int i;
    p = (int*)malloc(n*sizeof(int));
    rep(i, n){ p[i]=-1; }
}
int find(int x){
    if( p[x]<0 ){ return x; }
    else{ return ( p[x] = find(p[x]) ); }
}
char unite(int *x, int *y){
    *x=find(*x), *y=find(*y);
    if( *x==*y ) return 0; // none process
    // make size(x) smaller than size(y)
    // x, y: leader of group, p[x]<p[y] => size(x)>size(y)
    if( p[*x]<p[*y] ) swap(x, y);
    // merge x to y
    p[*y] += p[*x]; // size merge
    p[*x] = *y;
    return 1;
}
// ==========================================================================
