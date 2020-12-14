#include<stdio.h>
#include<stdlib.h>

#define rep(i, n) for(i=0;i<n;i++)

int compare(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}
int main(void){

    int i, n, m, *a;

    scanf("%d", &n);
    scanf("%d", &m);
    a = (int*)malloc((m+2)*sizeof(int));
    rep(i, m) scanf("%d", &a[i+1]);
    a[0] = 0; a[m+1] = n+1;
    
    //rep(i, m+2) printf("%d ", a[i]); putchar('\n');
    qsort(a, m+2, sizeof(int), compare);
    //rep(i, m+2) printf("%d ", a[i]); putchar('\n');

    int cnt=0, min=1000000004;
    rep(i, m+1){
        int diff=a[i+1]-a[i]-1;
        if( diff==0 ) continue;
        min=min>diff?diff:min;
    }
    
    //rep(i, m+2) printf("%d ", a[i]); putchar('\n');
    //printf("min range: %d\n", min);
    
    rep(i, m+1){
        int diff=a[i+1]-a[i]-1, add;
        if( diff==0 ) continue;
        add = (diff-1)/min + 1;
        //print("add: %d\n", add);
        cnt += add;
    }
    printf("%d\n", cnt);

    return 0;

}
