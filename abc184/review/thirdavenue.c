#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

// Pair =========================================================================
typedef int PairValue;
typedef struct ThreePair{
    PairValue first;
    PairValue second;
    PairValue third;
}Pair;
Pair *PairInit(PairValue, PairValue, PairValue); 
// ------------------------------------------------------------------------------

// FIFO List =====================================================================
typedef Pair* ListNodeValue;

typedef struct LinearList{
    ListNodeValue val;
    struct LinearList *next;
} ListNode;
ListNode *NodeInit(ListNodeValue, ListNode*);
void NodePrepend(ListNode**, ListNodeValue);
void NodeInsert(ListNode*, ListNodeValue);
typedef struct FIFO_Queue{
    int size;
    ListNode *first;
    ListNode *last;
} Queue;
Queue* QueueInit(void);
void enqueue(Queue*, ListNodeValue);
ListNodeValue dequeue(Queue*);
int empty(Queue*);
// ------------------------------------------------------------------------------

int main(void){
    int i, j, k, h, w, ans=-1;
    int vi[]={1,0,-1,0}, vj[]={0,1,0,-1};
    char **str;

    int **grid;
    Queue *task;

    scanf("%d %d", &h, &w);
    str=(char**)malloc(h*sizeof(char*));
    grid=(int**)malloc(h*sizeof(int*));
    rep(i, h){
        str[i]=(char*)malloc((w+1)*sizeof(char));
        scanf("%s", str[i]);
        grid[i]=(int*)malloc(w*sizeof(int));
    }

    task = QueueInit();
    rep(i, h) rep(j, w){
        grid[i][j]=-1;
        if( str[i][j]=='S' ){ grid[i][j]=0; enqueue(task, PairInit(i,j,0)); }
    }

    while( !empty(task) ){
        Pair *p=dequeue(task);
        int x, y, cnt;
        i=p->first; j=p->second; cnt=(p->third)+1;
        free(p);

        rep(k, 4){
            y=i+vi[k], x=j+vj[k];
            if( x<0 || w<=x || y<0 || h<=y ) continue;
            if( str[y][x]=='G' ){ ans=cnt; break; }
            if( str[y][x]=='#' ) continue;
            if( grid[y][x]!=-1 ) continue;

            grid[y][x]=cnt;
            enqueue(task, PairInit(y, x, cnt));
        }
        
        if( str[i][j]<'a' || str[i][j]>'z' ) continue;
        rep(y, h) rep(x, w){
            if( i==y && j==x ) continue;
            if( str[i][j]==str[y][x] ){
                grid[y][x]=cnt;
                enqueue(task, PairInit(y, x, cnt));
                str[y][x]='.';
            }
        }
        str[i][j]='.';
    }

    //putchar('\n');
    //rep(i, h) printf("%s\n", str[i]);

    printf("%d\n", ans);

    return 0;

}


// ------------------------------------------------------------------------------
Pair *PairInit(PairValue x, PairValue y, PairValue z){
    Pair *p;
    p=(Pair*)malloc(sizeof(Pair));
    if( p ){ p->first=x; p->second=y; p->third=z; }
    return p;
} 
// ==============================================================================
// ------------------------------------------------------------------------------
ListNode *NodeInit(ListNodeValue val, ListNode *next){
    ListNode *lnptr;
    lnptr = (ListNode*)malloc(sizeof(ListNode));
    if( lnptr ){
        lnptr-> val = val;
        lnptr-> next = next;
    }
    return lnptr;
}
void NodePrepend(ListNode **ln_ptrptr, ListNodeValue val){
    ListNode *ln_ptr;
    ln_ptr = NodeInit(val, *ln_ptrptr);
    if( ln_ptr ) *ln_ptrptr = ln_ptr;
}
void NodeInsert(ListNode *ln_ptr, ListNodeValue val){
    ListNode *new_ptr, *next_ptr;
    next_ptr = ln_ptr->next;
    new_ptr = NodeInit(val, next_ptr);
    ln_ptr-> next = new_ptr;
}

Queue* QueueInit(){
    Queue *q;
    q=(Queue*)malloc(sizeof(Queue));
    if( q ){ q->size=0; q->first=NULL; q->last=NULL; }
}
void enqueue(Queue *q, ListNodeValue val){
    if( q->size==0 ){
        NodePrepend(&(q->first), val);
        q->last=q->first;
        q->size=1;
    }else{
        NodeInsert(q->last, val);
        q->last = (q->last)->next;
        (q->size)++;
    }
}
ListNodeValue dequeue(Queue *q){
    ListNode *next_ptr;
    ListNodeValue val;
    next_ptr=(q->first)->next; val = (q->first)->val;

    free(q->first);
    q->first = next_ptr;
    if( next_ptr==NULL ) q->last=NULL;
    (q->size)--;
    return val;
}
int empty(Queue *q){ return q->size==0?1:0; }
// ==============================================================================
