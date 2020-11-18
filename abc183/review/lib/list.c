#include<stdio.h>
#include<stdlib.h>

// LinearList ===================================================================
// [val0, -]-> [val1, -]-> ... -> NULL
typedef int ListNodeValue;
typedef struct LinearList{
    ListNodeValue val;
    struct LinearList *next;
} ListNode;

ListNode *NodeInit(ListNodeValue, ListNode*);
void PrintList(ListNode*);
void NodePrepend(ListNode**, ListNodeValue);
void NodeAppend(ListNode**, ListNodeValue);
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
void PrintList(ListNode *ln_ptr){
    ListNode *iptr;
    printf("{ ");
    for( iptr=ln_ptr; iptr!=NULL; iptr=iptr->next){
        ListNodeValue val=iptr->val;
        // ListNodeValue is 'int'
        printf(" %d", val);
        // ListNodeValie is 'int*'
        //printf(" %d", *val);
    }
    printf(" }\n");
}
void NodePrepend(ListNode **ln_ptrptr, ListNodeValue val){
    ListNode *ln_ptr;
    ln_ptr = NodeInit(val, *ln_ptrptr);
    if( ln_ptr ) *ln_ptrptr = ln_ptr;
}
void NodeAppend(ListNode **ln_ptrptr, ListNodeValue val){
    ListNode *ln_ptr;
    ln_ptr = NodeInit(val, NULL);
    while( *ln_ptrptr!=NULL ) ln_ptrptr=&((*ln_ptrptr)->next); 
    *ln_ptrptr = ln_ptr;
}
// ==============================================================================

int main(void){

    int i;
    ListNode *ln;

    ln = NodeInit(0, NULL);
    for(i=1;i<10;i++){
        if( i%2==1 ) NodeAppend(&ln, i);
        else NodePrepend(&ln, i);
    }

    PrintList(ln);

    return 0;
}
