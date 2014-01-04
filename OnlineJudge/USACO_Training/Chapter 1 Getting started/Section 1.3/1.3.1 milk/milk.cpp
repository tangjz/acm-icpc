/*
ID: tangjin2
LANG: C++
TASK: milk
*/
#include<stdio.h>
int milk[1001]={},N,M,ans=0;
int main()
{
   freopen("milk.in","r",stdin);
   freopen("milk.out","w",stdout);
   int i=0,x,y;
   scanf("%d%d",&N,&M);
   while(M--)
   {
      scanf("%d%d",&x,&y);
      milk[x]+=y;
   }
   while(N)
   {
      if(milk[i])
         if(N>milk[i])
         {
            ans+=i*milk[i];
            N-=milk[i];
         }
         else
         {
            ans+=i*N;
            N=0;
         }
      ++i;
   }
   printf("%d\n",ans);
   fclose(stdin);
   fclose(stdout);
   return 0;
}
