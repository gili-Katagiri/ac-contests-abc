#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define rep(i, n) for(i=0;i<n;i++)
// AVL Tree =======================================================================
typedef int keyType;
typedef int valueType;
typedef struct AVLTreeMap{
    keyType key;
    valueType value;
    char height; // N=2**128-1=340282366920938463463374607431768211455
    struct AVLTreeMap *child[2]; // 0: left, 1: right
}avlMap;
keyType key(avlMap*);
int height(avlMap*);
int bias(avlMap*);
int compare(keyType x, keyType y);
char avlInsert(avlMap**, keyType, valueType);
char avlDelete(avlMap**, keyType);
avlMap* findKey(avlMap*, keyType);
avlMap* findUpperBound(avlMap*, keyType);
avlMap* findLowerBound(avlMap*, keyType);
avlMap** inorderTraversal(avlMap*, int); 

void printAVL(avlMap*);
void printAVLMap(avlMap*);
char charMax(char x, char y){ return x>y?x:y; }
// --------------------------------------------------------------------------------

int main(void){
    int i, n=4000000;
    avlMap *avl=NULL;
    avlMap **inorder;
    clock_t s, e;
    
    s = clock();
    rep(i, n) avlInsert(&avl, 2*i, i);
    e = clock();
    printf("insert: %.3f (sec)\n", (double)(e-s)/CLOCKS_PER_SEC);
    //printAVLMap(avl);
    
    s = clock();
    inorder = inorderTraversal(avl, n);
    e = clock();
    printf("traversal: %.3f (sec)\n", (double)(e-s)/CLOCKS_PER_SEC);
    //rep(i,n) printf("%d ", inorder[i]->key); 
    //putchar('\n');
    

    while( scanf("%d", &i) ){
        avlMap *f;
        if( i==0 ){
            printf("find: ");
            s = clock();
            scanf("%d", &i);
            f=findKey(avl, i);
        }else if(i==1){
            printf("upper: ");
            s = clock();
            scanf("%d", &i);
            f=findUpperBound(avl, i);
        }else if(i==-1){
            printf("lower: ");
            s = clock();
            scanf("%d", &i);
            f=findLowerBound(avl, i);
        }else break;
        e = clock();
        printf("bin-search: %.3f (sec)\n", (double)(e-s)/CLOCKS_PER_SEC);
        printAVL(f);
    }

    return 0;
}

// system functions ---------------------------------------------------------------
avlMap* avlInit(keyType, valueType);
// set-status
int measure(avlMap*);
// rotation
void singleRotate(avlMap**, int);
void doubleRotate(avlMap**, int);
// delete
char overWriteMax(avlMap**, avlMap*);
// balance
int balancing(avlMap**);

// depend keyType and valueType: implemeted 'int'
keyType key(avlMap *node){ return node==NULL?-1:node->key; }
int compare(keyType x, keyType y){ return x>y?1:(x==y?0:-1); }
void printAVL(avlMap *avl_ptr){
    avlMap *lc, *rc;
    if( avl_ptr==NULL ){ printf("Not Found\n"); return; }
    printf("<%p>:\n", avl_ptr);
    printf("\tkey=%d val=%d height=%d\n",\
            avl_ptr->key, avl_ptr->value, avl_ptr->height);
    lc=avl_ptr->child[0]; rc=avl_ptr->child[1];
    printf("\tchild key: left=%d right=%d\n", key(lc), key(rc));
}
void printAVLMap(avlMap *avl_ptr){
    avlMap *lc, *rc;
    if( avl_ptr==NULL ) return;
    printAVL(avl_ptr);
    lc=avl_ptr->child[0]; rc=avl_ptr->child[1];
    printAVLMap(lc); printAVLMap(rc); 
}

// init 
avlMap* avlInit(keyType key, valueType val){
    avlMap *avl_ptr;
    avl_ptr = (avlMap*)malloc(sizeof(avlMap));
    if( avl_ptr ){
        avl_ptr->key=key;
        avl_ptr->value=val;
        avl_ptr->height=1;
        avl_ptr->child[0]=NULL;
        avl_ptr->child[1]=NULL;
    }
    return avl_ptr;
}

// insert
char avlInsert(avlMap **root, keyType key, valueType value){
    char change, cflag;
    if( *root==NULL ){
        *root=avlInit(key, value);
        change=1;
    }else if( (cflag=compare(key, (*root)->key))==0 ){ 
        (*root)->value = value;
        change=0;
    }else{
        cflag = (cflag==-1?0:1);
        change=avlInsert(&( (*root)->child[cflag]), key, value);
        if( change ) change=balancing(root);
    }
    return change;
}

// delete
char avlDelete(avlMap **root, keyType key){
    char change, cflag;
    if( *root==NULL ) return 0;
    else if( (cflag=compare(key, (*root)->key))==0 ){ // delete
        avlMap **lc_ptrptr;
        if(*( lc_ptrptr=&((*root)->child[0]) ) == NULL){ // left-child is not exist
            // pull up right child
            *root = (*root)->child[1];
            return 1;
        }else{ // search left max node and overwrite
            change = overWriteMax(lc_ptrptr, *root);
            if( change ) change=balancing(root);
        }
    }else{
        cflag = (cflag==-1?0:1);
        change = avlDelete(&( (*root)->child[cflag]), key);
        if( change ) change=balancing(root);
    }
    return change;
}
char overWriteMax(avlMap **target, avlMap *delete){
    char change;
    if( (*target)->child[1]==NULL ){
        avlMap *lc;
        lc=(*target)->child[0];
        // set key-value
        delete->key=(*target)->key;
        delete->value=(*target)->value;
        // release and pull up left child
        free(*target);
        *target = lc;
        change=1;
    }else{ //exits right child
        change=overWriteMax(&((*target)->child[1]), delete);
        if( change ) change=balancing(target);
    }
    return change;
}

// search
avlMap* findKey(avlMap *avl_ptr, keyType key){
    int cflag;
    while( avl_ptr!=NULL ){
        cflag = compare(key, avl_ptr->key);
        if( cflag==0 ) break;
        else if( cflag==1 ) avl_ptr=avl_ptr->child[1];
        else avl_ptr=avl_ptr->child[0];
    }
    return avl_ptr;
}
// find nearest value, 1: upperound, 0:lowerbound
avlMap* nearestBound(avlMap *avl_ptr, keyType key, int upper){
    int cflag;
    int uflag[]={-1, 1};
    avlMap *nptr=NULL;
    while( avl_ptr!=NULL ){
        cflag = compare(key, avl_ptr->key);
        if( cflag==0 ){ nptr=avl_ptr;  break; }
        else if( cflag == uflag[upper] ){
            nptr = avl_ptr;
            avl_ptr=avl_ptr->child[upper];
        }else avl_ptr = avl_ptr->child[1-upper];
    }
    return nptr;
}
avlMap* findUpperBound(avlMap *avl_ptr, keyType key){
    return nearestBound(avl_ptr, key, 1);
}
avlMap* findLowerBound(avlMap *avl_ptr, keyType key){
    return nearestBound(avl_ptr, key, 0);
}
// depth-first-search
void stockInorder(avlMap *avl_ptr, avlMap ***stockpoint){
    if( avl_ptr==NULL ) return;
    stockInorder(avl_ptr->child[0], stockpoint);
    **stockpoint = avl_ptr;
    (*stockpoint)++;
    stockInorder(avl_ptr->child[1], stockpoint);
}
avlMap** inorderTraversal(avlMap *avl_ptr, int n){
    int i;
    avlMap **values, **itr;
    values = (avlMap**)malloc(n*sizeof(avlMap*));
    itr = values;
    stockInorder(avl_ptr, &itr);
    return values;
} 

// Balance
int balancing(avlMap **root){
    int b, preh, rflag=-1;
    avlMap *child;
    preh = height(*root);
    b = bias(*root);

    if( b==2 ) rflag=1;
    else if( b==-2) rflag=0;
    if( rflag!=-1 ){
        child = (*root)->child[rflag];
        if( b*bias(child)<0 ) doubleRotate(root, rflag);
        else singleRotate( root, rflag);
    }
    return (measure(*root)!=preh);
}

// status
int height(avlMap *node){ return node==NULL?0:node->height; }
int measure(avlMap *node){
    return node->height=(charMax(height(node->child[0]),height(node->child[1]))+1);
}
int bias(avlMap *node){ return height(node->child[1]) - height(node->child[0]); }

// Rotations
// cdir=1: root-right-Rotation, cdir=0: root-left-Rotation
void singleRotate(avlMap **r, int cdir){
    avlMap *s;
    s=(*r)->child[cdir];
    (*r)->child[cdir]=s->child[1-cdir];
    s->child[1-cdir]=*r;
    measure(*r); measure(s);
    *r=s;
}
// cdir=1: cright=root-child[right]; cright-left-Rotation->root-right-Rotation
// cdir=0: cleft =root-child[ left]; cleft-right-Rotation-> root-left-Rotation
void doubleRotate(avlMap **r, int cdir){
    singleRotate( &((*r)->child[cdir]), 1-cdir);
    singleRotate( r, cdir);
}
// ================================================================================
