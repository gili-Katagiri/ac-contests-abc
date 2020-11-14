#include<stdio.h>

int sumof(long long n){
    int sum=0;

    while( n!=0 ){
        sum += (n%10);
        n = n/10;
    }

    return sum;
}

void search(long long n, int res[]){
    int onecnt=0, twocnt=0;

    while( n!=0 ){
        int d=n%10;
        if( (d%3)==1 ) onecnt++;
        if( (d%3)==2 ) twocnt++;
        n/=10;
    }
    res[0]=onecnt; res[1]=twocnt;
}

int main(void){
    long long n;
    int sum, res[2], ans=-1;

    scanf("%lld", &n);
    sum = sumof(n);
    
    if( sum<3 ){
        printf("-1\n"); return 0; 
    }else if( sum%3==0 ){ ans=0; }
    else{
        search(n, res);
        if( sum%3==2 ){
            if( res[1]>0 ) ans=1;
            else if( res[0]>1 ) ans=2;
        }else{
            if( res[0]>0 ) ans=1;
            else if( res[1] > 1 ) ans=2;
        }
    }

    if( ans==1 && n<10 ) ans=-1;
    else if( ans==2 && n<100 ) ans=-1;
    printf("%d\n", ans);

    return 0;
}

