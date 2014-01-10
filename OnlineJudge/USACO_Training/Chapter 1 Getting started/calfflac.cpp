/*
ID: tangjin2
LANG: C++
TASK: calfflac
*/
#include<stdio.h>
#include<string.h>
char ch[256001]={},temp[1000]={},s[256001]={};
int p[256001]={};
int check(char x)
{
   if(x>='A'&&x<='Z')return 1;
   if(x>='a'&&x<='z')return 1;
   return 0;
}
char transfrom(char x)
{
   if(x>='a')return x-32;
   return x;
}
int main()
{
   freopen("calfflac.in","r",stdin);
   freopen("calfflac.out","w",stdout);
   int n,m=0,max=0,x,y,i,j;
   while(gets(temp))
   {
      strcat(ch,temp);
      strcat(ch,"\n");
      memset(temp,0,sizeof(temp));
   }
   n=strlen(ch);
   for(i=0;i<n;++i)
      if(check(ch[i]))
      {
         p[m]=i;
         s[m++]=transfrom(ch[i]);
      }
   for(i=0;i<m;++i)
   {
      for(j=0;i-j>=0&&i+j<m;++j)
      {
         if(s[i-j]!=s[i+j])break;
         if(j*2+1>max)
         {
            max=j*2+1;
            x=p[i-j];y=p[i+j];
         }
      }
      for(j=0;i-j>=0&&i+j+1<m;++j)
      {
         if(s[i-j]!=s[i+j+1])break;
         if(j*2+2>max)
         {
            max=j*2+2;
            x=p[i-j];y=p[i+j+1];
         }
      }
   }
   printf("%d\n",max);
   for(i=x;i<=y;++i)printf("%c",ch[i]);
   printf("\n");
   fclose(stdin);
   fclose(stdout);
   return 0;
}
