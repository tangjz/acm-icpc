#include <string>
#include <cstdio>
#include <algorithm>
const int maxn = 101;
int n, m, len, cnt[maxn], ans1, ans2;
std::string seq[maxn];
char buf[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", buf);
		seq[i] = buf;
	}
	scanf("%s", buf);
	len = ((std::string)buf).length();
	std::sort(seq, seq + n);
	n = std::unique(seq, seq + n) - seq;
	for(int i = 0; i < n; ++i)
		++cnt[seq[i].length()];
	for(int i = 1; i < len; ++i)
		ans1 += cnt[i];
	ans2 = ans1 + cnt[len] - 1;
	printf("%d %d\n", ans1 + ans1 / m * 5 + 1, ans2 + ans2 / m * 5 + 1);
	return 0;
}
