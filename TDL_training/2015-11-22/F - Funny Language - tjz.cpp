#include <set>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxm = 101, maxs = 26;
struct Node
{
	int val, cnt[maxs];
	bool operator == (const Node &t) const
	{
		if(val != t.val)
			return 0;
		for(int i = 0; i < maxs; ++i)
			if(cnt[i] != t.cnt[i])
				return 0;
		return 1;
	}
	bool operator < (const Node &t) const
	{
		if(val != t.val)
			return val < t.val;
		for(int i = 0; i < maxs; ++i)
			if(cnt[i] != t.cnt[i])
				return cnt[i] < t.cnt[i];
		return 0;
	}
	bool have(const Node &t) const
	{
		for(int i = 0; i < maxs; ++i)
			if(cnt[i] < t.cnt[i])
				return 0;
		return 1;
	}
} a[maxn], tmp;
set<Node> Hash;
set<string> AAA;
int n, m, tot;
char str[maxm];
void print(Node x)
{
	printf("insert : ");
	for(int i = 0; i < maxs; ++i)
		for(int j = 0; j < x.cnt[i]; ++j)
			putchar('A' + i);
	printf(" : %d\n", x.val);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		AAA.clear();
		memset(a, 0, m * sizeof(Node));
		for(int i = 0; i < m; ++i)
		{
			scanf("%s", str);
			for(int j = 0; str[j]; ++j)
				++a[i].cnt[(int)str[j] - 'A'];
			AAA.insert((string)str);
		}
		tot = 0;
		Hash.clear();
		memset(&tmp, 0, sizeof(Node));
		for(int i = 0; i < maxs; ++i)
		{
			++tmp.cnt[i];
			tmp.val = 0;
			for(int j = 0; j < m; ++j)
				if(a[j].have(tmp))
					++tmp.val;
			Hash.insert(tmp);
			++tot;
			--tmp.cnt[i];
		}
		for( ; tot > n + m; --tot)
			Hash.erase(Hash.begin());
		for(int i = 1; i <= n; )
		{
			tmp = *Hash.rbegin();
			Hash.erase(tmp);
			--tot;
			int len = 0;
			for(int j = 0; j < maxs; ++j)
				for(int k = 0; k < tmp.cnt[j]; ++k)
					str[len++] = 'A' + j;
			str[len] = '\0';
			while(i <= n)
			{
				if(!AAA.count((string)str))
				{
					puts(str);
					++i;
				}
				if(!next_permutation(str, str + len))
					break;
			}
			if(i > n)
				break;
			int pos = 0;
			for(int j = 0; j < maxs; ++j)
				if(tmp.cnt[j])
					pos = j;
			for(int j = pos; j < maxs; ++j)
			{
				++tmp.cnt[j];
				tmp.val = 0;
				for(int j = 0; j < m; ++j)
					if(a[j].have(tmp))
						++tmp.val;
				//print(tmp);
				if(Hash.count(tmp))
				{
					--tmp.cnt[j];
					continue;
				}
				if(tot < n + m)
				{
					Hash.insert(tmp);
					++tot;
				}
				else if(tot == n + m && Hash.begin() -> val < tmp.val)
				{
					Hash.erase(Hash.begin());
					Hash.insert(tmp);
				}
				--tmp.cnt[j];
			}
		}
	}
	return 0;
}
