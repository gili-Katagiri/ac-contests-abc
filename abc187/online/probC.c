#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

// AVL Tree =======================================================================
typedef char* keyType;
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


int main(void) {

    int i, n, cnt=0;
    
    avlMap *lst=NULL;
    avlMap **inorder;

    // input----------
    scanf("%d", &n);
    rep(i, n){
        int j, adj=1, notFind=0;
        char input[11]={'\0'};
        char *addchar;

        addchar = (char*)malloc(11*sizeof(char));
        scanf("%s", input);
        if( input[0]=='!' ){
            for(j=1;j<11;j++) addchar[j-1] = input[j];
            addchar[10] = '\0';
        }else{
            rep(j, 11) addchar[j] = input[j];
            addchar[10] = '\0';
            adj++;
        }
        if( findKey(lst, addchar)==NULL ) notFind=1;
        avlInsert(&lst, addchar, adj);
        if( notFind ) cnt++;
        else free(addchar);
    }
    // ----------
    
    //printf("count: %d\n", cnt);
    //printAVLMap(lst);
    inorder = inorderTraversal(lst, cnt);
    
    rep(i, cnt){
        avlMap *node;
        node = inorder[i];
        if( node->value==3 ){
            printf("%s\n", node->key);
            return 0;
        }
    }

    printf("satisfiable\n");

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
keyType key(avlMap *node){ return node==NULL?'\0':node->key; }
int compare(keyType x, keyType y){ //return x>y?1:(x==y?0:-1); }
    int i=0;
    while( x[i]!='\0' && y[i]!='\0' && x[i]==y[i] ) i++;
    if (x[i]=='\0' && y[i]=='\0'){
        return 0;
    }else if( x[i]<y[i] ){
        return -1;
    }else{
        return 1;
    }

}
void printAVL(avlMap *avl_ptr){
    avlMap *lc, *rc;
    if( avl_ptr==NULL ){ printf("Not Found\n"); return; }
    printf("<%p>:\n", avl_ptr);
    printf("\tkey=%s val=%d height=%d\n",\
            avl_ptr->key, avl_ptr->value, avl_ptr->height);
    lc=avl_ptr->child[0]; rc=avl_ptr->child[1];
    printf("\tchild key: left=%s right=%s\n", key(lc), key(rc));
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
        // OR 
        (*root)->value |= value;
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
