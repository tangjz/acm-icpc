/*
ID: tangjin2
LANG: C++
TASK: checker
*/
#include<stdio.h>
int n,s=0,ldis[25]={},rdis[25]={},linedis[13]={},pos[13]={};
void backtrack(int i)
{
   int j;
   if(i==n)
   {
      if(s<3)
      {
         for(j=0;j<n-1;j++)printf("%d ",pos[j]+1);
         printf("%d\n",pos[j]+1);
      }
      s++;
      return;
   }
   for(j=0;j<n;j++)
   {
      if(linedis[j]==0&&ldis[i+j]==0&&rdis[j-i+13]==0)
      {
         pos[i]=j;
         linedis[j]=1;
         ldis[i+j]=1;
         rdis[j-i+13]=1;
         backtrack(i+1);
         linedis[j]=0;
         ldis[i+j]=0;
         rdis[j-i+13]=0;
      }
   }
}
int main()
{
   freopen("checker.in","r",stdin);
   freopen("checker.out","w",stdout);
   scanf("%d",&n);
   backtrack(0);
   printf("%d\n",s);
   fclose(stdin);
   fclose(stdout);
   return 0;
}
