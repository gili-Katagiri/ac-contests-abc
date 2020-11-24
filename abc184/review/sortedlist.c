#include<stdio.h>
#include<stdlib.h>

// SortedLinkedList as SortList
// ================================================================================
typedef int ListNodeValue;
typedef struct SortedLinkedList{
    ListNodeValue val;
    struct SortedLinkedList *next;
} SortList;
SortList* NodeInit(ListNodeValue, SortList*);
void NodePrepend(SortList**, SortList*);
void ValuePrepend(SortList**, ListNodeValue);
void NodeInsert(SortList**, SortList*);
void ValueInsert(SortList**, ListNodeValue);
void ListMerge(SortList**, SortList*);
void ListSwap(SortList**, SortList**);
void PrintList(SortList*);
void PrintValue(ListNodeValue);
int compare(ListNodeValue, ListNodeValue);
// --------------------------------------------------------------------------------

int main(void){
    int i, n=500;
    SortList *sl1=NULL, *sl2=NULL;

    for(i=n; i>0; i--) ValuePrepend(&sl2, 2*i);
    for(i=n; i>0; i--) ValuePrepend(&sl1, 3*i);
    //PrintList(sl1);
    //PrintList(sl2);
    
    ListMerge(&sl1, sl2);
    PrintList(sl1);
    return 0;
}

// --------------------------------------------------------------------------------
SortList* NodeInit(ListNodeValue val, SortList *next){
    SortList *sl_ptr;
    sl_ptr = (SortList*)malloc(sizeof(SortList));
    if( sl_ptr ){
        sl_ptr-> val = val;
        sl_ptr-> next = next;
    }
    return sl_ptr;
}
void NodePrepend(SortList **sl_ptrptr, SortList *sl_ptr){
    sl_ptr->next = *sl_ptrptr;
    *sl_ptrptr = sl_ptr;
}
void ValuePrepend(SortList **sl_ptrptr, ListNodeValue val){
    SortList *sl_ptr;
    sl_ptr = NodeInit(val, *sl_ptrptr);
    if( sl_ptr ) *sl_ptrptr = sl_ptr;
}
void NodeInsert(SortList **sl_ptrptr, SortList *sl_ptr){
    if( *sl_ptrptr==NULL ){ NodePrepend(sl_ptrptr, sl_ptr); }
    else{
        SortList *tmp=(*sl_ptrptr)->next;
        (*sl_ptrptr)->next = sl_ptr;
        sl_ptr->next = tmp;
    }
}
void ValueInsert(SortList **sl_ptrptr, ListNodeValue val){
    if( *sl_ptrptr==NULL ){ ValuePrepend(sl_ptrptr, val); }
    else{
        SortList *sl_ptr;
        sl_ptr = NodeInit(val, (*sl_ptrptr)->next);
        if( sl_ptr ) (*sl_ptrptr)->next = sl_ptr;
    }
}
void ListMerge(SortList **sptrptr, SortList *tptr){
    SortList *sptr, *nsptr, *mgptr;
    sptr = *sptrptr;
    if( sptr==NULL ){ *sptrptr=tptr; return; }
    if( tptr==NULL ){ return; }
    if( compare(tptr->val, sptr->val) ) ListSwap(&sptr, &tptr);
    mgptr=sptr; *sptrptr=sptr; sptr=sptr->next;
    while( sptr!=NULL ){
        if( compare(tptr->val, sptr->val) ) ListSwap(&sptr, &tptr);
        nsptr = sptr->next;
        NodeInsert(&mgptr, sptr);
        mgptr = sptr;
        sptr = nsptr;
    }
    mgptr->next = tptr;
}

// utility
void ListSwap(SortList **a, SortList **b){
    SortList *temp;
    temp=*a; *a=*b; *b=temp;
}
void PrintList(SortList *sl_ptr){
    printf("{ ");
    for( ; sl_ptr!=NULL; sl_ptr=sl_ptr->next){
        putchar(' '); PrintValue(sl_ptr->val);
    }
    printf(" }\n");
}
// ListNodeValue is 'int'
void PrintValue(ListNodeValue val){ printf("%d", val); }
int compare(ListNodeValue x, ListNodeValue y){ return x<y; }
// ================================================================================
