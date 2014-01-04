/*
ID: tangjin2
LANG: C++
TASK: crypt1
*/
#include<stdio.h>
int N,used[10]={},number[6]={},ans=0;
int check()
{
   int tmp1=((number[0]*10+number[1])*10+number[2])*number[3];
   if(tmp1>=1000)return 0;
   int tmp2=((number[0]*10+number[1])*10+number[2])*number[4];
   if(tmp2>=1000)return 0;
   int tmp3=tmp1*10+tmp2;
   if(tmp2>=10000)return 0;
   while(tmp1)
   {
      if(!used[tmp1%10])return 0;
      tmp1/=10;
   }
   while(tmp2)
   {
      if(!used[tmp2%10])return 0;
      tmp2/=10;
   }
   while(tmp3)
   {
      if(!used[tmp3%10])return 0;
      tmp3/=10;
   }
   return 1;
}
void dfs(int dep)
{
   if(dep==5)
   {
      if(check())++ans;
      return;
   }
   int i;
   for(i=1;i<=9;++i)
      if(used[i])
      {
         number[dep]=i;
         dfs(dep+1);
         number[dep]=0;
      }
}
int main()
{
   freopen("crypt1.in","r",stdin);
   freopen("crypt1.out","w",stdout);
   int i,x;
   scanf("%d",&N);
   for(i=1;i<=N;++i)
   {
      scanf("%d",&x);
      ++used[x];
   }
   dfs(0);
   printf("%d\n",ans);
   fclose(stdin);
   fclose(stdout);
   return 0;
}
