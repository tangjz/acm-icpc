#include <iostream>
using namespace std;
int a, b, n;
bool flag = true;
int gcd(int x,int y) {if(!y) return x; return gcd(y, x % y);}
int main()
{
    ios::sync_with_stdio(false);
    cin >> a >> b >> n;
    while(n > 0)
    {
        flag = !flag;
        if(!flag) n -= gcd(n, a);
        else n -= gcd(n, b);
    }
    cout << flag << endl;
    return 0;
}
