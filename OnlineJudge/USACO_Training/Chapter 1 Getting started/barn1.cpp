/*
ID: tangjin2
LANG: C++
TASK: barn1
*/
#include<stdio.h>
int stall[200]={},number[201]={},M,S,C,ans;
void qsort(int low,int high)
{
   if(low>=high)return;
   int i=low,j=high;
   number[0]=number[(i+j)/2];
   number[(i+j)/2]=number[i];
   while(i<j)
   {
      while(i<j&&number[j]>number[0])--j;
      if(i<j)number[i]=number[j];
      while(i<j&&number[i]<number[0])++i;
      if(i<j)number[j]=number[i];
   }
   number[i]=number[0];
   qsort(low,i-1);
   qsort(i+1,high);
}
int main()
{
   freopen("barn1.in","r",stdin);
   freopen("barn1.out","w",stdout);
   int i,x,y;
   scanf("%d%d%d",&M,&S,&C);
   for(i=1;i<=C;++i)scanf("%d",&number[i]);
   qsort(1,C);
   ans=number[C]-number[1]+1;
   for(i=1;i<C;++i)++stall[number[i+1]-number[i]-1];
   i=S-1;
   --M;
   while(M&&i>0)
   {
      if(stall[i])
      {
         if(M>=stall[i])
         {
            ans-=i*stall[i];
            M-=stall[i];
         }
         else
         {
            ans-=i*M;
            M=0;
         }
      }
      --i;
   }
   printf("%d\n",ans);
   fclose(stdin);
   fclose(stdout);
   return 0;
}
