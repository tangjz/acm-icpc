#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
char temp;
string s, tmp, ans;
queue<string> q;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    while(n--)
    {
        cin >> tmp;
        s += " ";
        s += tmp;
    }
    q.push("");
    while(1)
    {
        tmp = q.front();
        q.pop();
        for(temp = 'a'; temp <= 'z'; ++temp)
        {
            ans = tmp + temp;
            if(s.find(ans) == string::npos)
            {
                cout << ans << endl;
                return 0;
            }
            else q.push(ans);
        }
    }
}
