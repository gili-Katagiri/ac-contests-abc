#include<stdio.h>

#define rep(i,n) for(i=0;i<n;i++)
#define MOD 1000000007
#define MAX 2003

int h, w;
int grid[MAX][MAX];

void fill(int i, int j, int vi, int vj){
    int ti=i+vi, tj=j+vj, base;

    if( grid[i][j]==-1 ) return;
    base = grid[i][j];

    while( ti<h && tj<w && grid[ti][tj]!=-1){
        grid[ti][tj] += base;
        grid[ti][tj] = grid[ti][tj]%MOD;
        ti+=vi; tj+=vj;
    }

}

int main(void){
    
    int i, j;
    char str[MAX];
    
    scanf("%d %d", &h, &w);

    rep( i, h){
        scanf("%s", str);
        rep( j, w){
            if( str[j]=='#') grid[i][j]=-1;
            else grid[i][j] = 0;
        }
    }

    grid[0][0] = 1;
    rep(i, h) rep(j,w){
            int k, vi[]={0, 1, 1}, vj[]={1, 0, 1};
            rep(k, 3) fill(i, j, vi[k], vj[k]);
    }

    printf("%d\n", grid[h-1][w-1]);
    

    return 0;
}
