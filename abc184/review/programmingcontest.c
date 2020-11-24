#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

// SortedLinkedList as SortList
// ================================================================================
typedef long long ListNodeValue;
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

SortList* create(SortList *s, int x){
    if( s==NULL ) return NULL;
    SortList *t;
    t = create(s->next, x);
    ValuePrepend(&t, (s->val)+x);
    return t;
}

int main(void){
    int i, n;
    int *a;
    long long T, max=0;
    SortList *s=NULL, *t=NULL;

    scanf("%d %lld", &n, &T);
    a=(int*)malloc(n*sizeof(int));
    rep(i, n) scanf("%d", &a[i]);

    ValuePrepend(&s, 0);
    ValuePrepend(&t, 0);
    rep(i, n){
        SortList *c;
        c = create(s, a[i]);
        ListMerge(&s, c);
        ListSwap(&s, &t);
    }
    //printf("s: "); PrintList(s); 
    //printf("t: "); PrintList(t); 
    
    for(; s!=NULL; s=s->next){
        long long x=s->val, cand;
        SortList *itr;
        if( x>T ) break;
        if( x==T ){ max=x; break; }
        if( max==T ) break;
        for(itr=t; itr->next!=NULL&&(itr->next)->val<=T-x; itr=itr->next) continue;
        cand=x+itr->val;
        max = cand>max?cand:max;
    }

    printf("%lld\n", max);

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
void PrintValue(ListNodeValue val){ printf("%lld", val); }
int compare(ListNodeValue x, ListNodeValue y){ return x<y; }
