#include<stdio.h>

#define rep(i, n) for(i=0;i<n;i++)

#define MAX 200001
int main(void){
    int i, n, x;
    char str[MAX];

    scanf("%d %d", &n, &x);
    scanf("%s", str);

    rep(i, n){
        if( str[i]=='o' ) x++;
        else if( x>0) x--;
    }

    printf("%d\n", x);

    return 0;

}
