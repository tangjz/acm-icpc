/*
ID: tangjin2
LANG: C++
TASK: sprime
*/
#include<stdio.h>
#include<math.h>
int N,n=1;
int check(int x)
{
   if(x<2)return 0;
   int i,j=(int)sqrt(x);
   for(i=2;i<=j;++i)
      if(x%i==0)return 0;
   return 1;
}
void make(int x)
{
   if(x>=n)
   {
      printf("%d\n",x);
      return;
   }
   int i;
   for(i=1;i<=9;++i)
      if(check(10*x+i))make(10*x+i);
}
int main()
{
   freopen("sprime.in","r",stdin);
   freopen("sprime.out","w",stdout);
   scanf("%d",&N);
   while(N--!=1)n*=10;
   make(0);
   fclose(stdin);
   fclose(stdout);
   return 0;
}
