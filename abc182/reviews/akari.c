#include<stdio.h>

#define HW 1501
#define rep(i, n) for(i=0; i<n; i++)

char light[HW][HW];
char block[HW][HW];
char  grid[HW][HW];
char visit[HW][HW];
char akari[HW][HW];

char di[]={-1, 0, 1, 0};
char dj[]={ 0, 1, 0,-1};

int memorec( int i, int j, int v, int h, int w){
    if( i<0 || j<0 || i>=h || j>=w ) return 0;
    if( light[i][j] ) return 1;
    if( block[i][j] ) return 0;

    if( visit[i][j] ) return grid[i][j];

    visit[i][j] = 1;
    grid[i][j] = memorec(i+di[v], j+dj[v], v, h, w);
    return grid[i][j];
}

int main(void){
    int i, j, k, v;
    int n, m, h, w, cnt=0;

    scanf("%d %d %d %d", &h, &w, &n, &m);
    
    rep(i, h) rep(j, w){
        light[i][j] = 0;
        block[i][j] = 0;
        akari[i][j] = 0;
         grid[i][j] = 0;
    }

    rep(k, n){
        int a,b;
        scanf("%d %d", &a, &b);
        light[a-1][b-1] = 1;
    }

    rep(k, m){
        int a,b;
        scanf("%d %d", &a, &b);
        block[a-1][b-1] = 1;
    }
    
    rep(v, 4){
        rep(i, h) rep(j, w) visit[i][j]=0;
        rep(i, h) rep(j, w) if( memorec( i, j, v, h, w) ) akari[i][j]=1;
    }

    rep(i, h) rep(j, w) if( akari[i][j] ) cnt++;
    printf("%d", cnt);

    return 0;
}

