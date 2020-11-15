#include<stdio.h>

#define rep(i,n) for(i=0;i<n;i++)

int main(void){
    
    int sx, sy, gx, gy;
    double slope, b, tx;

    scanf("%d %d %d %d", &sx, &sy, &gx, &gy);
    
    gy *= -1;

    slope = (double)(gy-sy) / (gx-sx);
    b = sy-slope*sx;
    tx = -b/slope;
    
    printf("%f\n", tx);

    return 0;
}
