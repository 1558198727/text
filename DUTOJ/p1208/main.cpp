#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstring>
using namespace std;

long long CNM(int n,int m){
    long long ret=1;
    for(int k=1;k<=m;k++)
    {
        ret=(ret*(n-m+k))/k;//����˷����������㣨m-n+k��/k�������������
        ret%=1000000007;
    }
return ret%1000000007;
}

int main()
{
    long long n;
    scanf("%lld",&n);
    printf("%lld\n",CNM(8*n-2,4*n-1)/2);

    return 0;
}
