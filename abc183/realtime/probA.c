#include<stdio.h>

#define rep(i,n) for(i=0;i<n;i++)

int relu( int x){
    return x>=0 ? x:0;
}

int main(void){
    
    int x=0;
    
    scanf("%d", &x);
    printf("%d\n", relu(x));

    return 0;
}
