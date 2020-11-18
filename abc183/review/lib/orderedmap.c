#include<stdio.h>
#include<stdlib.h>
#define fep(i,n) for(i=0;i<n;i++)

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
Map *MapAdd(Map*, int, MapValue);
void MapMerge(Map*, Map*);
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
    printf("{ %d: %d", mptr->key, mptr->val);
    for(mptr=mptr->next; mptr!=NULL; mptr=mptr->next){
        printf(", %d: %d", mptr->key, mptr->val);
    }
    printf("}\n");
}
Map *MapAdd(Map *mptr, int key, MapValue val){
    if( key < mptr->key ){ //prepend
        // can't use prepend: mptr may not be set on initial
        Map *new_ptr;
        // deep copy
        new_ptr=MapInit(mptr->key, mptr->val, mptr->next);
        // re-write
        mptr->key=key; mptr->val=val; mptr->next=new_ptr; 
        return mptr;
    } 
    else if( key==mptr->key ){  mptr->val+=val; return mptr; }
    
    while( mptr!=NULL ){
        Map *imp = mptr->next;
        if( imp==NULL || key<imp->key ){ //append
            return (mptr->next=MapInit(key, val, imp));
        }
        else if( key==imp->key ){ imp->val+=val; return imp; }
        else if( imp->key < key ) mptr = mptr->next;
    }
    return NULL;
}
void MapMerge(Map *tomap, Map *frommap){
    Map *dmp;
    while( frommap!=NULL ){
        dmp = frommap;
        frommap=frommap->next;
        tomap = MapAdd(tomap, dmp->key, dmp->val);
        free(dmp);
    }
}
// ======================================================================



int main(void){
    
    int i;
    Map *mptr, *mmptr;
    mptr = MapInit(0, 0, NULL);
    MapAdd(mptr, 1, 3);
    MapAdd(mptr, 99, 0);
    MapAdd(mptr, 2, 15);
    MapAdd(mptr, -1, 44);
    MapAdd(mptr, 0, 9841);

    mmptr = MapInit(4, 1, NULL);
    MapAdd(mmptr, 99, -82);
    MapAdd(mmptr, 99, 0);
    MapAdd(mmptr, 4, 33);
    MapAdd(mmptr, 0, -841);
    MapAdd(mmptr, 10000, 123);
    
    PrintMap(mptr);
    PrintMap(mmptr);

    MapMerge(mptr, mmptr);
    PrintMap(mptr);

    return 0;
}
