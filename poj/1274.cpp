#include<stdio.h>
#include<string.h>
int n,m,count=0,link[401]={0};
bool g[201][201]={false},y[201];
bool find(int v)
{
 int i;
 for(i=1;i<=m;i++)
 {
  if(g[v][i]&&!y[i])
  {
   y[i]=true;
   if(link[i+200]==0||find(link[i+200]))
   {
    link[i+200]=v;
    return true;
   }
  }
 }
 return false;
}
int main()
{
 int i,j,si,a;
 while(scanf("%d%d",&n,&m)!=EOF){
  for(i=1;i<=n;i++)
  {
   scanf("%d",&si);
   memset(g[i]+1,0,m*sizeof(bool));
   for(j=1;j<=si;j++)
   {
    scanf("%d",&a);
    g[i][a]=true;
   }
  }
  count=0;
  memset(link+201,0,m*sizeof(int));
  for(i=1;i<=n;i++)
  {
   memset(y+1,0,m*sizeof(bool));
   if(find(i))count++;
  }
  printf("%d\n",count);
 }
 return 0;
}
