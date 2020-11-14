#include<stdio.h>

int main(void){
    int a[101], n, i, k, max=0, maxk=-1, lim=0;

    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &a[i]);
        if( lim<a[i] ) lim=a[i];
    }

    for( k=2; k<=lim; k++ ){
        int cnt=0;
        for( i=0; i<n; i++){
            if ( a[i]%k==0 ){ cnt++; }
        }
        if( max<cnt ){ max=cnt; maxk=k; }
    }

    printf("%d\n", maxk);

    return 0;
}

