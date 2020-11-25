#include<stdio.h>
#include<stdlib.h>

// SortedLinkedList as SortedList
// ================================================================================
typedef int nodeValue;
typedef struct SortedLinkedList{
    nodeValue val;
    struct SortedLinkedList *next;
} SortedList;
SortedList* nodeInit(nodeValue, SortedList*);
void nodePrepend(SortedList**, SortedList*);
void valuePrepend(SortedList**, nodeValue);
void nodeInsert(SortedList**, SortedList*);
void valueInsert(SortedList**, nodeValue);

void listMerge(SortedList**, SortedList*);
void listSwap(SortedList**, SortedList**);
void printList(SortedList*);
void printValue(nodeValue);
int compare(nodeValue, nodeValue);
// --------------------------------------------------------------------------------

int main(void){
    int i, n=500;
    SortedList *sl1=NULL, *sl2=NULL;

    for(i=n; i>0; i--) valuePrepend(&sl2, 2*i);
    for(i=n; i>0; i--) valuePrepend(&sl1, 3*i);
    //printList(sl1);
    //printList(sl2);
    
    listMerge(&sl1, sl2);
    printList(sl1);
    return 0;
}

// --------------------------------------------------------------------------------
SortedList* nodeInit(nodeValue val, SortedList *next){
    SortedList *sl_ptr;
    sl_ptr = (SortedList*)malloc(sizeof(SortedList));
    if( sl_ptr ){
        sl_ptr-> val = val;
        sl_ptr-> next = next;
    }
    return sl_ptr;
}
void nodePrepend(SortedList **sl_ptrptr, SortedList *sl_ptr){
    sl_ptr->next = *sl_ptrptr;
    *sl_ptrptr = sl_ptr;
}
void valuePrepend(SortedList **sl_ptrptr, nodeValue val){
    SortedList *sl_ptr;
    sl_ptr = nodeInit(val, *sl_ptrptr);
    if( sl_ptr ) *sl_ptrptr = sl_ptr;
}
void nodeInsert(SortedList **sl_ptrptr, SortedList *sl_ptr){
    if( *sl_ptrptr==NULL ){ nodePrepend(sl_ptrptr, sl_ptr); }
    else{
        SortedList *tmp=(*sl_ptrptr)->next;
        (*sl_ptrptr)->next = sl_ptr;
        sl_ptr->next = tmp;
    }
}
void valueInsert(SortedList **sl_ptrptr, nodeValue val){
    if( *sl_ptrptr==NULL ){ valuePrepend(sl_ptrptr, val); }
    else{
        SortedList *sl_ptr;
        sl_ptr = nodeInit(val, (*sl_ptrptr)->next);
        if( sl_ptr ) (*sl_ptrptr)->next = sl_ptr;
    }
}
void listMerge(SortedList **sptrptr, SortedList *tptr){
    SortedList *sptr, *nsptr, *mgptr;
    sptr = *sptrptr;
    if( sptr==NULL ){ *sptrptr=tptr; return; }
    if( tptr==NULL ){ return; }
    if( compare(tptr->val, sptr->val) ) listSwap(&sptr, &tptr);
    mgptr=sptr; *sptrptr=sptr; sptr=sptr->next;
    while( sptr!=NULL ){
        if( compare(tptr->val, sptr->val) ) listSwap(&sptr, &tptr);
        nsptr = sptr->next;
        nodeInsert(&mgptr, sptr);
        mgptr = sptr;
        sptr = nsptr;
    }
    mgptr->next = tptr;
}

// utility
void listSwap(SortedList **a, SortedList **b){
    SortedList *temp;
    temp=*a; *a=*b; *b=temp;
}
void printList(SortedList *sl_ptr){
    printf("{ ");
    for( ; sl_ptr!=NULL; sl_ptr=sl_ptr->next){
        putchar(' '); printValue(sl_ptr->val);
    }
    printf(" }\n");
}
// nodeValue is 'int'
void printValue(nodeValue val){ printf("%d", val); }
int compare(nodeValue x, nodeValue y){ return x<y; }
// ================================================================================
