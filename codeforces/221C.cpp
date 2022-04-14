#include <iostream>
#include <algorithm>
using namespace std;
int n, a[100001] = {}, b[100001] = {}, cnt = 0;
int main()
{
    int i;
    ios::sync_with_stdio(false);
    cin >> n;
    for(i = 0; i < n; ++i)
    {
        cin >> a[i];
        b[i] = a[i]; 
    }
    sort(b, b + n);
    for(i = 0; i < n; ++i)
        if(a[i] != b[i])
        {
            if(cnt == 2) break;
            else ++cnt;
        }
    if(i < n) cout << "NO" << endl;
    else cout << "YES" << endl;
    return 0;
}