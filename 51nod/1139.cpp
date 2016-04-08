#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
struct Equ
{
	LL num[5];
	bool operator < (const Equ &t) const
	{
		for(int i = 0; i < 5; ++i)
			if(num[i] != t.num[i])
				return num[i] < t.num[i];
		return 0;
	}
	bool valid() const
	{
		for(int i = 1; i < 5; ++i)
			if(num[i - 1] == num[i])
				return 0;
		return 1;
	}
	void print() const
	{
		for(int i = 0; i < 5; ++i)
			printf("%lld%c", num[i], " \n"[i == 4]);
	}
	void sort()
	{
		std::sort(num, num + 5);
	}
} ;
set<Equ> Hash;
LL n;
int cnt;
void dfs(Equ cur)
{
	cur.sort();
	if(Hash.count(cur))
		return;
	Hash.insert(cur);
	for(int i = 0; i < 5; ++i)
	{
		LL tmp1 = n + cur.num[i];
		for(int j = 0; j < 5; ++j)
			if(i != j)
				tmp1 /= cur.num[j];
		if(!tmp1)
			continue;
		tmp1 = 1;
		for(int j = 0; j < 5; ++j)
			if(i != j)
				tmp1 *= cur.num[j];
		tmp1 -= cur.num[i];
		LL tmp2 = cur.num[i];
		cur.num[i] = tmp1;
		dfs(cur);
		cur.num[i] = tmp2;
	}
}
int main()
{
	scanf("%lld", &n);
	dfs((Equ){1, 1, 3, 3, 4});
	for(set<Equ>::iterator it = Hash.begin(); it != Hash.end(); ++it)
		if(it -> valid())
			++cnt;
	if(!cnt)
		puts("No Solution");
	else
	{
		printf("%d\n", cnt);
		for(set<Equ>::iterator it = Hash.begin(); it != Hash.end(); ++it)
			if(it -> valid())
				it -> print();
	}
	return 0;
}
