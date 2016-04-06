#include <iostream>
using namespace std;
const string ans[] = {"", "Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};
int n;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    while(n > 5) n = (n - 4) >> 1;
    cout << ans[n] << endl;
    return 0;
}
