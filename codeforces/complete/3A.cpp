#include <iostream>
using namespace std;
int x_s, y_s, x_t, y_t, ans = 0; string out[8] = {};
int main()
{
    int i; char ch;
    ios::sync_with_stdio(false);
    cin >> ch >> y_s, x_s = ch - 'a' + 1;
    cin >> ch >> y_t, x_t = ch - 'a' + 1;
    while(x_s > x_t && y_s < y_t) out[ans++] = "LU", --x_s, ++y_s;
    while(x_s > x_t && y_s > y_t) out[ans++] = "LD", --x_s, --y_s;
    while(x_s < x_t && y_s < y_t) out[ans++] = "RU", ++x_s, ++y_s;
    while(x_s < x_t && y_s > y_t) out[ans++] = "RD", ++x_s, --y_s;
    while(x_s > x_t) out[ans++] = "L", --x_s;
    while(x_s < x_t) out[ans++] = "R", ++x_s;
    while(y_s < y_t) out[ans++] = "U", ++y_s;
    while(y_s > y_t) out[ans++] = "D", --y_s;
    cout << ans << endl;
    for(i = 0; i < ans; ++i) cout << out[i] << endl;
    return 0;
}
