#include<stdio.h>
int main()
{
	/*10个值初始值都为0，0代表狐狸没有到过的山洞*/
	/*a[0]为1号洞，a[9]为10号洞*/
   int a[10]={0};
   int i,k=-1;
   /*k为狐狸每次经过的洞号*/
   for(i=1;i<=1000;i++)
   {
	   k=(k+i)%10;/*k每次加i，代表跳过i-1个洞*/
	   //printf("%d  ", k);
       a[k]=1;   /*赋值为1代表狐狸进入过该洞*/
   }
   for(i=0;i<10;i++)
	   if(a[i]==0)
          printf("%d  ", i+1);
   return 0;
}
 