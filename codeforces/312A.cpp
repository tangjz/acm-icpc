#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
string lyd = "miao.", shy = "lala.", tmp;
int main()
{
    bool flag1, flag2;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        getline(cin, tmp); if(i == 0 && tmp == "") getline(cin, tmp);
        if(tmp.find(lyd) == 0) flag1 = true; else flag1 = false;
        if(tmp.rfind(shy) != string::npos && tmp.rfind(shy) + 5 == tmp.length()) flag2 = true; else flag2 = false;
        if(flag1 && !flag2) cout << "Rainbow's" << endl;
        else if(!flag1 && flag2) cout << "Freda's" << endl;
        else cout << "OMG>.< I don't know!" << endl;
    }
    return 0;
}
