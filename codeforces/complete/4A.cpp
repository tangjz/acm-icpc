#include <iostream>
using namespace std;
int n;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    if(n > 3 && n % 2 == 0) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
