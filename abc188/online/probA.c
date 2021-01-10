#include<stdio.h>
#include<stdlib.h>

#define rep(i,n) for(i=0;i<n;i++)

int main(void) {

    int a, b, diff;
    scanf("%d %d", &a, &b);
    
    diff = a-b;
    if( diff<3 && diff>-3 ){
        printf("Yes\n");
    }else{
        printf("No\n");
    }

    return 0;

}
