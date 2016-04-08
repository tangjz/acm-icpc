#include <map>
#include <cstdio>
using namespace std;
const char* str = "JOI";
int n, cnt[3], ans;
map<pair<int, int>, int> Hash;
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d\n", &n);
	Hash[make_pair(0, 0)] = 0;
	for(int i = 1; i <= n; ++i)
	{
		char ch;
		scanf("%c", &ch);
		for(int j = 0; j < 3; ++j)
			if(ch == str[j])
				++cnt[j];
		if(Hash.count(make_pair(cnt[1] - cnt[0], cnt[2] - cnt[1])))
			upd(ans, i - Hash[make_pair(cnt[1] - cnt[0], cnt[2] - cnt[1])]);
		else
			Hash[make_pair(cnt[1] - cnt[0], cnt[2] - cnt[1])] = i;
	}
	printf("%d\n", ans);
	return 0;
}
