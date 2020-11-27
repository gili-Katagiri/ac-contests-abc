#include<stdio.h>
#include<stdlib.h>

// Output-Restricted queue =======================================================
typedef int sllValue;

typedef struct SinglyLinkedList{
    sllValue val;
    struct SinglyLinkedList *next;
} SLL;
SLL* sllInit(sllValue, SLL*);
void sllPrepend(SLL**, sllValue);
void sllInsert(SLL*, sllValue);
typedef struct OutputRestrictedorque{
    int size;
    SLL *first;
    SLL *last;
} orque;
orque* orqueInit(void);
void enqueue(orque*, sllValue);
void push(orque*, sllValue);
sllValue dequeue(orque*);
int empty(orque*);
// -------------------------------------------------------------------------------
int main(void){
    int i;
    orque *q;
    q = orqueInit();

    for(i=0;i<40;i++){
        if( i%3==0 ) push(q, i);
        else enqueue(q, i);
    }

    while( !empty(q) ){
        int v=dequeue(q);
        printf("%d\n", v);
    }
    return 0;

}
// ------------------------------------------------------------------------------
SLL* sllInit(sllValue val, SLL *next){
    SLL *lnptr;
    lnptr = (SLL*)malloc(sizeof(SLL));
    if( lnptr ){
        lnptr-> val = val;
        lnptr-> next = next;
    }
    return lnptr;
}
void sllPrepend(SLL **ln_ptrptr, sllValue val){
    SLL *ln_ptr;
    ln_ptr = sllInit(val, *ln_ptrptr);
    if( ln_ptr ) *ln_ptrptr = ln_ptr;
}
void sllInsert(SLL *ln_ptr, sllValue val){
    SLL *new_ptr, *next_ptr;
    next_ptr = ln_ptr->next;
    new_ptr = sllInit(val, next_ptr);
    ln_ptr-> next = new_ptr;
}

orque* orqueInit(){
    orque *q;
    q=(orque*)malloc(sizeof(orque));
    if( q ){ q->size=0; q->first=NULL; q->last=NULL; }
}
void emptyPrepend(orque *q, sllValue val){
    sllPrepend( &(q->first), val);
    q->last = q->first;
    q->size=1;
}
void enqueue(orque *q, sllValue val){
    if( empty(q) ) emptyPrepend(q, val);
    else{
        sllInsert(q->last, val);
        q->last = (q->last)->next;
        (q->size)++;
    }
}
void push(orque *q, sllValue val){
    if( empty(q) ) emptyPrepend(q, val);
    else{    
        sllPrepend(&(q->first), val);
        (q->size)++;
    }
}
sllValue dequeue(orque *q){
    sllValue val; SLL *next_ptr;
    val = (q->first)->val; next_ptr=(q->first)->next;
    free(q->first);
    q->first = next_ptr;
    if( next_ptr==NULL ) q->last=NULL;
    (q->size)--;
    return val;
}
int empty(orque *q){ return q->size==0?1:0; }
// ==============================================================================
