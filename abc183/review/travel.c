#include<stdio.h>

#define rep(i,n) for(i=0;i<n;i++)
#define NMAX 8

// next permutation ==============================
int perm[NMAX+1]; // with sentinel
int itrs[NMAX];
int size;

void swap(int[], int, int);
void move(int[], int, int);
void perm_init(int);
int next_permutations(void);

void swap(int a[], int i, int j){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
void move(int a[], int f, int t){
    int i, tmp=a[f];
    for(i=f;i<t;i++) a[i]=a[i+1];
    a[t] = tmp;
}
void perm_init(int n){
    int i;
    size = n;
    rep(i, n){ perm[i]=i; itrs[i]=1; }
    perm[n]=NMAX; // sentinel [ 0, 1, 2, 50]
}
int next_permutation(void){
    int sp; 

    for( sp=size-2; sp>=0; sp--){ // n>1, sp>=0
        
        // is [ perm[sp+1], ... ] dict-order?
        if( perm[sp+1]<perm[sp+2] ){ // sp=n-2: true anytime because exist sentinel
            int tp=sp+itrs[sp];
            if( tp<size ){ // swap update
                swap( perm, sp, tp);
                itrs[sp]++; // next swap point
                return 1;
            }else{ // move update: [3, 2, 0, 1]-> [3, 0, 1, 2]
                move(perm, sp, size-1);
                itrs[sp]=1;
                continue;
            }
        }

    }
    // exists next perm
    return 0;
}

// ===============================================


// recursive  ====================================
void permutation(int a[], int s, int t){
    int i;

    if( s==t-1 ){
        // process  ========================
        rep(i, t){
            printf("%d", a[i]);
            putchar( i!=t-1? ' ' : '\n');
        }
        // =================================
        return ;
    }

    for(i=1; i<t-s; i++){
        permutation(a, s+1, t);
        swap( a, s, s+i );
    }
    permutation(a, s+1, t);
    move(a, s, t-1);

}
// ===============================================

int main(void){
    
    int i, j, n, k, ans=0;
    int t[NMAX][NMAX];

    scanf("%d %d", &n, &k);
    rep(i, n) rep(j,n) scanf("%d", &t[i][j]);

    putchar('\n');
    perm_init(n);
    do{
        // main process  =========================
        int sum=0;
        if( perm[0] != 0 ) break;
        // debug 
        //rep(i, n) printf("%d ", perm[i]);
        //putchar('\n');

        rep( i, n-1) sum+=t[perm[i]][perm[i+1]];
        sum += t[perm[n-1]][perm[0]];
        if( sum==k ) ans++;
        // =======================================

    } while( next_permutation() );
    
    printf("%d\n", ans);

    return 0;
}
