/*
 * 分三种情况枚举答案  
 */
#include <cstring>
#include <iostream>
using namespace std;
int n, mine[10001] = {}, f[10001] = {}, ans = 0;
void find()
{
	int i;
	for(i = 3; i <= n; ++i) f[i] = mine[i - 1] - f[i - 1] - f[i - 2];
	if(f[n] + f[n - 1] == mine[n]) ++ans;
}
int main()
{
	int i;
	ios::sync_with_stdio(false);
	cin >> n;
	for(i = 1; i <= n; ++i) cin >> mine[i];
	if(!mine[1]) find();
	else if(mine[1] == 2) { f[1] = f[2] = 1; find(); }
	else if(mine[1] == 1)
	{
	    f[1] = 1; find();
		memset(f, 0, sizeof(f));
		f[2] = 1; find();
	}
	cout << ans << endl;
	return 0;
}
