#include <iostream>
using namespace std;
long long n;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    if(n == 1) cout << 1 << endl;
    else if(n == 2) cout << 2 << endl;
    else if(n & 1) cout << n * (n - 1) * (n - 2) << endl;
    else if(n % 3) cout << n * (n - 1) * (n - 3) << endl;
    else cout << (n - 1) * (n - 2) * (n - 3) << endl;
    return 0;
}
