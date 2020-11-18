#include<stdio.h>
#include<stdlib.h>
#define rep(i, n) for( i=0;i<n;i++ )

// Map[keys: int, vals: MapValue] ============================================= 
typedef int MapValue;
const int incsize = 10;
typedef struct IntMap{
    int size;
    int maxsize;
    int *keys;
    MapValue *vals;
} Map;

Map *MapInit(void);
int MapKeyIndex(Map*, int);
MapValue *MapKeyValue(Map*, int);
void MapExtend(Map*);
void MapWrite(Map*, int, MapValue);
void PrintMap(Map*);
//  --------------------------------------------------------------------------- 

Map *MapInit(void){
    Map *mptr;
    mptr = (Map*)malloc(sizeof(Map));
    if( mptr ){
        mptr-> size = 0;
        mptr-> maxsize = incsize;
        mptr-> keys = (int*)malloc(incsize*sizeof(int));
        mptr-> vals = (MapValue*)malloc(incsize*sizeof(MapValue));
    }
    return mptr;
}
int MapKeyIndex(Map *mptr, int key){
    int i;
    rep(i, mptr->size) if( (mptr->keys)[i]==key ) return i;
    return -1;
}
MapValue *MapKeyValue(Map *mptr, int key){
    int idx=MapKeyIndex(mptr, key);
    if( idx==-1 ) return NULL;
    else return &((mptr-> vals)[idx]);
}
void MapExtend(Map *mptr){
    int i, maxsize=(mptr->maxsize)+incsize;
    int *newkeys;
    MapValue *newvals;

    newkeys = (int*)malloc(maxsize*sizeof(int));
    newvals = (MapValue*)malloc(maxsize*sizeof(MapValue));

    rep(i, mptr->size){
        newkeys[i] = (mptr-> keys)[i];
        newvals[i] = (mptr-> vals)[i];
    }
    
    mptr-> keys = newkeys;
    mptr-> vals = newvals;
    mptr-> maxsize = maxsize;
}
void MapWrite(Map *mptr, int key, MapValue val){
    int ekey=MapKeyIndex(mptr, key);
    if( ekey==-1 ){ // if map[key] is NOT exists
        int size;
        size = (mptr-> size)++;
        if( size==(mptr->maxsize) ) MapExtend(mptr);
        (mptr-> keys)[size] = key;
        (mptr-> vals)[size] = val;
    }else{ // overwrite
        (mptr-> vals)[ekey] = val;
    }
}
void PrintMap(Map *mptr){
    int i;
    printf("mapsize= %d (maxsize: %d)\n", mptr->size, mptr->maxsize);
    rep(i, mptr->size){
        printf("map[%3d] = %4d\n", (mptr->keys)[i],(mptr->vals)[i]);
    }
}
// ============================================================================ 

int main(void){
    
    int i;
    Map *mptr;

    mptr = MapInit();

    MapWrite(mptr, 0, -1);
    MapWrite(mptr, 3, -3);
    MapWrite(mptr, 5, 10);

    for(i=20; i>15; i--) MapWrite(mptr, i, i+1);
    *MapKeyValue(mptr, 5) = -5;
    PrintMap(mptr);

    return 0;
}
