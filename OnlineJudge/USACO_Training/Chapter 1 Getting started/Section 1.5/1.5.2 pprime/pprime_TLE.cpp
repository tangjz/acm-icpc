/*
ID: tangjin2
LANG: C++
TASK: pprime
*/
#include <stdio.h>
#include <math.h>
int main()
{
   freopen("pprime.in","r",stdin);
   freopen("pprime.out","w",stdout);
   int a,b,i,j,k,l;
   scanf("%d %d",&a,&b);
   if(a%2==0)++a;
   for(;a<=b;a+=2)
   {
      k=0;
      i=a;
      while(i)
      {
         k=k*10+i%10;
         i/=10;
      }
      if(a==k)
      {
         l=(int)sqrt(a);
         if(l%2==0)++l;
         for(j=3;j<=l;j+=2)if(a%j==0)break;
         if(j>l)printf("%d\n",a);
      }
   }
   fclose(stdin);
   fclose(stdout);
   return 0;
}
