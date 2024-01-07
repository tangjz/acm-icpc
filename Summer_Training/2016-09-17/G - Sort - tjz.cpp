#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 200001;
int t, n, mx, a[maxn];
struct Queue
{
	int que[maxn], L, R;
	void clear()
	{
		L = R = 0;
	}
	void copy(const int &len, const int seq[])
	{
		L = 0, R = len;
		memcpy(que, seq, len * sizeof(int));
	}
	int pop_front()
	{
		int ret = que[L++];
		if(L == maxn)
			L = 0;
		return ret;
	}
	void push_front(const int &x)
	{
		--L;
		if(L < 0)
			L = maxn - 1;
		que[L] = x;
	}
	void push_back(const int &x)
	{
		que[R++] = x;
		if(R == maxn)
			R = 0;
	}
} qA, qB;
bool check(int sz)
{
	int rem = n, cost = 0;
	for(qA.copy(n, a); (rem - 1) % (sz - 1); ++rem)
		qA.push_front(0);
	qB.clear();
	while(rem > 1)
	{
		int tmp = 0;
		for(int cnt = min(rem, sz); cnt; --cnt)
			if(qB.L == qB.R || qA.L != qA.R && qA.que[qA.L] <= qB.que[qB.L])
				tmp += qA.pop_front();
			else
				tmp += qB.pop_front();
		if(tmp > mx - cost)
			return 0;
		cost += tmp;
		qB.push_back(tmp);
		rem -= min(rem, sz) - 1;
	}
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &mx);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		int L = 2, R = n;
		while(L < R)
		{
			int M = L + R >> 1;
			if(check(M))
				R = M;
			else
				L = M + 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
