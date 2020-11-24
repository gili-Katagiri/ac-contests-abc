#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)
#define MAX 2001

// FIFO List =====================================================================
typedef int ListNodeValue;

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
// -------------------------------------------------------------------------------

int main(void){
    int i;
    Queue *q;
    q = QueueInit();

    rep(i, 4000000) enqueue(q, i);

    while( !empty(q) ){
        int v=dequeue(q);
        printf("%d\n", v);
    }
    return 0;

}


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
    (q->size)--;
    return val;
}
int empty(Queue *q){ return q->size==0?1:0; }
// ==============================================================================
