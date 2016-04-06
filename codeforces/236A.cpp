#include <iostream>
using namespace std;
int i, j, length, cnt = 0;
bool word[26] = {};
string name = "";
int main()
{
    ios::sync_with_stdio(false);
    cin >> name;
    length = name.length();
    for(i = 0; i < length; ++i)
    {
        j = name[i] - 'a';
        if(!word[j]) word[j] = true, ++cnt;
    }
    if(cnt & 1) cout << "IGNORE HIM!" << endl;
    else cout << "CHAT WITH HER!" << endl;
    return 0;
}
