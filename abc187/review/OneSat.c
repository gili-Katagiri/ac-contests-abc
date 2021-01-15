#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define rep(i,n) for(i=0;i<n;i++)

// SinglyLinkedList---------------------------------
typedef char* sllValue;
typedef struct SinglyLinkedList{
    sllValue val;
    struct SinglyLinkedList *next;
} SLL;
SLL* sllInit(sllValue, SLL*);
void sllPrepend(SLL**, sllValue);

int is_same_value(sllValue, sllValue);
SLL *sllFind(SLL*, sllValue);
// -------------------------------------------------

// HashSet: OpenAddressing--------------------------
typedef sllValue rawValue;
typedef struct OpenAddressingHashSet{
    const int table_size_;
    SLL** hashTable_;
} HashSet;
HashSet* hashTableInit(HashSet*);
// raw value to int
int hashAlgorithm(rawValue, int);
void hashSetAdd(HashSet*, rawValue);
rawValue hashSetFind(HashSet*, rawValue);
// -------------------------------------------------

int main(void) {

    int i, j, n, m=12;
    char **input_list;
    HashSet set={ .table_size_=899, .hashTable_=NULL };
    hashTableInit(&set);

    // input----------
    scanf("%d", &n);
    input_list = (char**)malloc(n*sizeof(char*));
    rep(i, n){
        input_list[i] = (char*)malloc(m*sizeof(char));
        //rep(j, m) input[j] = '\0';
        scanf("%s", input_list[i]);
        hashSetAdd( &set, input_list[i]);
    }
    // ----------
    rep(i, n){
        char *input, str[m+1], *raw;
        input = input_list[i];
        str[0] = '!'; rep(j, m) str[j+1] = input[j];
        raw = hashSetFind(&set, str);
        if( raw==NULL ) continue;
        else{
            printf("%s\n", input);
            return 0;
        }
    }
    printf("satisfiable\n");

    return 0;

}


// SinglyLinkedList---------------------------------
int is_same_value(sllValue x, sllValue y){
    return ( strcmp(x, y)==0 );
}

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
SLL *sllFind(SLL *ln_ptr, sllValue val){
    while( ln_ptr!=NULL ){
        sllValue nodeval;
        nodeval = ln_ptr-> val;
        if( is_same_value(val, nodeval) ) break;
        ln_ptr = ln_ptr->next;
    }
    return ln_ptr;
}
//--------------------------------------------------

// HashSet: OpenAddressing--------------------------
HashSet* hashTableInit(HashSet *hs_ptr){
    int i, ts;
    ts = hs_ptr-> table_size_;
    if( hs_ptr ){
        hs_ptr-> hashTable_ = 
            (SLL**)malloc(ts*sizeof(SLL*));
        rep(i, ts){
            hs_ptr->hashTable_[i] = NULL;
        }
    }
    return hs_ptr;
}
int hashAlgorithm(rawValue r, int table_size){
    int h, i=0;
    h=0;
    while( r[i]!='\0' ){
        h = (h<<sizeof(char)) + (int)(r[i]);
        i++;
    }
    h %= table_size;
    /*
    h=1;
    while( r[i]!='\0' ){
        h = ( (int)(r[i])*(i+1)*h )%table_size;
        i++;
    }
    */
    /*
    h=1;
    for( c=&(r[0]); *c!='\0'; c++){
        h = ( (int)(*c)*h ) % table_size;
    }
    */
    //printf("hashed: %d\n", h);
    return h;
}
void hashSetAdd(HashSet *hs_ptr, rawValue val){
    int hval;
    SLL *node;
    hval = hashAlgorithm(val, hs_ptr->table_size_);
    node = sllFind( hs_ptr->hashTable_[hval], val);
    if( node ) return; 
    else sllPrepend( &(hs_ptr->hashTable_[hval]), val);
}
rawValue hashSetFind(HashSet *hs_ptr, rawValue val){
    int hval;
    SLL *node;
    hval = hashAlgorithm(val, hs_ptr->table_size_);
    node = sllFind( hs_ptr->hashTable_[hval], val);
    if( node ) return node->val;
    else return NULL;
}
//--------------------------------------------------
