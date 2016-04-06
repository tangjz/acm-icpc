#include <cmath>
#include <iostream>
using namespace std;
double x[3] = {}, y[3] = {}, r[3] = {};
double f(double X,double Y)
{
    int i;
    double tmp[3] = {}, ans = 0.0;
    for(i = 0; i < 3; ++i) tmp[i] = sqrt((x[i] - X) * (x[i] - X) + (y[i] - Y) * (y[i] - Y)) / r[i];
    for(i = 0; i < 3; ++i) ans += (tmp[i] - tmp[(i + 1) % 3]) * (tmp[i] - tmp[(i + 1) % 3]);
    return ans;
}
int main()
{
    int i;
    double X = 0.0, Y = 0.0, C = 1.0;
    for(i = 0; i < 3; ++i)
    {
        cin >> x[i] >> y[i] >> r[i];
        X += x[i];
        Y += y[i];
    }
    X /= 3;
    Y /= 3;
    while(C > 1e-5)
    {
        bool flag = false;
        if(f(X + C, Y) < f(X, Y)) flag = true, X += C;
        else if(f(X - C, Y) < f(X, Y)) flag = true, X -= C;
        if(f(X, Y + C) < f(X, Y)) flag = true, Y += C;
        else if(f(X, Y - C) < f(X, Y)) flag = true, Y -= C;
        if(!flag) C *= 0.5;
    }
    cout.precision(5);
    if(f(X, Y) < 1e-5) cout << X << ' ' << Y << endl;
    return 0;
}
