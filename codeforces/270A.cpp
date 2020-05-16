#include <iostream>
using namespace std;
int t, a;
int main()
{
    ios::sync_with_stdio(false);
    cin >> t;
    while(t-- && cin >> a)
        if(360 % (180 - a) == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    return 0;
}
