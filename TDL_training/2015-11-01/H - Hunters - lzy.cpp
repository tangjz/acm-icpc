#include <cstdio>

int T,x,y;
double p,q,a,b;

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d%d%lf%lf",&x,&y,&p,&q);
        a=q*(p*(x+y))+(1-q)*x;
        b=q*y+(1-q)*(p*(x+y));
        if (a<b) printf("wolf %.4f\n",b);
        else printf("tiger %.4f\n",a);
    }
    return 0;
}
