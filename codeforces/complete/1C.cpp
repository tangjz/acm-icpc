#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
double x[3], y[3], d[3], angle[4], r, p, s;
double fgcd(double a, double b)
{
   if(fabs(a - 0) < 1E-2) return b;
   if(fabs(b - 0) < 1E-2) return a;
   return fgcd(b, fmod(a, b));
}
int main()
{
   ios::sync_with_stdio(false);
   cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2];
   d[0] = sqrt((x[0] - x[1]) * (x[0] - x[1]) + (y[0] - y[1]) * (y[0] - y[1]));
   d[1] = sqrt((x[1] - x[2]) * (x[1] - x[2]) + (y[1] - y[2]) * (y[1] - y[2]));
   d[2] = sqrt((x[2] - x[0]) * (x[2] - x[0]) + (y[2] - y[0]) * (y[2] - y[0]));
   p = (d[0] + d[1] + d[2]) / 2;
   s = sqrt(p * (p - d[0]) * (p - d[1]) * (p - d[2]));
   r = d[0] * d[1] * d[2] / (4 * s);
   angle[0] = acos(1 - d[0] * d[0] / (2 * r * r));
   angle[1] = acos(1 - d[1] * d[1] / (2 * r * r));
   angle[2] = 2 * acos(-1.0) - angle[0] - angle[1];
   angle[3] = fgcd(angle[0], fgcd(angle[1], angle[2]));
   cout.flags(ios::fixed);
   cout.precision(6);
   cout << r * r * sin(angle[3]) / 2 * (2 * acos(-1.0) / angle[3]) << endl;
   return 0;
}
