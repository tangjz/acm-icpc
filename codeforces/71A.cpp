#include <iostream>
using namespace std;
int n, length;
string tmp;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    while(n--)
    {
        tmp.clear();
        cin >> tmp;
        length = tmp.length();
        if(length > 10) cout << tmp[0] << length - 2 << tmp[length - 1] << endl;
        else cout << tmp << endl;
    }
    return 0;
}
