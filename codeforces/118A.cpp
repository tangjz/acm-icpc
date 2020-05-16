#include <iostream>
#include <algorithm>
using namespace std;
const int add = 'a' - 'A';
int top = 0;
char ch[101] = {};
bool check()
{
    if(ch[top] <= 'Z') ch[top] += add;
    if(ch[top] == 'a' || ch[top] == 'e' || ch[top] == 'i' || ch[top] == 'o' || ch[top] == 'u' || ch[top] == 'y') return false;
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> ch;
    while(ch[top] != '\0')
    {
        if(check()) cout << '.' << ch[top];
        ++top;
    }
    cout << endl;
    return 0;
}
