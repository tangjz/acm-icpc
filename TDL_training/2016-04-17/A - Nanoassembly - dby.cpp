#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const double eps = 1e-12;
const int MAXN = 100300 + 5;
double x[MAXN],y[MAXN];
int n,m;

double cross(int a,int b,int c){
    double x1 = x[b] - x[a],x2 = x[c] - x[a],y1 = y[b] - y[a],y2 = y[c] - y[a];
    return y2 * x1 - y1 * x2;
}
inline double norm(double x,double y){
    return sqrt(x * x + y * y);
}
double getCos(int A,int B,int C){
    double xAB = x[A] - x[B],yAB = y[A] - y[B],xAC = x[A] - x[C],yAC = y[A] - y[C],xBC = x[B] - x[C],yBC = y[B] - y[C];
    return (xAB * xAB + yAB * yAB + xAC * xAC + yAC * yAC - xBC * xBC - yBC * yBC) / (2.0 * norm(xAB,yAB) * norm(xAC,yAC));
}
void ref(int a,int b,int c){
    if(x[a] == x[b]){
        x[c] = 2.0 * x[a] - x[c];
        return;
    }
    double xm = x[b] - x[a],ym = y[b] - y[a];
    double len = (norm(x[c] - x[b],y[c] - y[b]) * (-getCos(b,a,c))) / norm(xm,ym);
    xm *= len; ym *= len;
    xm += x[b]; ym += y[b];
    xm -= x[c]; ym -= y[c];
    xm *= 2.0; ym *= 2.0;
    x[c] += xm; y[c] += ym;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;++ i){
        scanf("%lf%lf",&x[i],&y[i]);
    }
    for(int i = n;i < n + (m << 1);i += 2){
        for(int j = i;j < i + 2;++ j)
            scanf("%lf%lf",&x[j],&y[j]);
        for(int j = 0;j < n;++ j)
        if(cross(i,i + 1,j) < -eps)
            ref(i,i + 1,j);
    }
    for(int i = 0;i < n;++ i) printf("%.6f %.6f\n",x[i],y[i]);
    return 0;
}
