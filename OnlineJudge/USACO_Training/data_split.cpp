const char *name="";//文件名 
const int maxN=8;
const int maxn=maxN+1;
#include<stdio.h>
#include<string.h>
int now;//当前位置 - 1 
char ch[100000],check[100],file[100];//分别是读入 判断 文件名 
void filter()
{
   memset(check,0,sizeof(check));
   sprintf(check,"------- test %d ----",now);
   while(1)
   {
      memset(ch,0,sizeof(ch));
      gets(ch);
      if(strcmp(ch,check)==0)break;
   }
   memset(file,0,sizeof(file));
   sprintf(file,"%s_%d.in",name,now);
   freopen(file,"w",stdout);
}
void make()
{
   if(now==1){filter();return;}
   memset(check,0,sizeof(check));
   if(now==maxn)sprintf(check,"Keep up the good work!");
   else sprintf(check,"------- test %d ----",now);
   while(1)
   {
      memset(ch,0,sizeof(ch));
      gets(ch);
      if(strcmp(ch,check)==0)break;
      printf("%s\n",ch);
   }
   fclose(stdout);
   if(now==maxn)return;
   memset(file,0,sizeof(file));
   sprintf(file,"%s_%d.in",name,now);
   freopen(file,"w",stdout);
}
int main()
{
   memset(file,0,sizeof(file));
   sprintf(file,"%s.txt",name);
   freopen(file,"r",stdin);
   for(now=1;now<=maxn;++now)make();
   fclose(stdout);
   fclose(stdin);
   return 0;
}
