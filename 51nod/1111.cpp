#include <stdio.h>
#include <algorithm>
#include <unordered_map>
typedef long long LL;
const int maxn = 1200001;
int n, L, R, pw, ppw, r, mod;
std::unordered_map<int, int> High, Low, tmp; // (value, curID)
int staHI, endHI, szLO;
std::pair<int, int> queHI[maxn], queLO[maxn], ans; // (value, preID or digit)
void exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % n)
		if(k & 1)
			ret = (LL)ret * x % n;
	return ret;
}
int mod_inv(int x, int p)
{
	int u, v;
	exgcd(x, p, u, v);
	return u < 0 ? u + p : u;
}
void print(int lenL, int curL)
{
	if(lenL == 1)
	{
		putchar('1');
		return;
	}
	int preL = queHI[curL].second;
	print(lenL - 1, preL);
	int state = 10LL * queHI[preL].first % n;
	putchar('0' + (state != queHI[curL].first));
}
void print()
{
	//printf("%d %d %d %d\n", L, queHI[ans.first].first, R, queLO[ans.second].first);
	print(L, ans.first);
	int posR = R, curR = ans.second;
	while(1)
	{
		int pos = queLO[curR].second;
		for(--posR; posR > pos; --posR)
			putchar('0');
		if(pos == -1)
			break;
		putchar('1');
		int state = queLO[curR].first - mod_pow(10, pos);
		if(state < 0)
			state += n;
		curR = Low[state];
	}
}
int main()
{
	scanf("%d", &n);
	// special check
	if(n == 1)
	{
		puts("1");
		return 0;
	}
	// Left
	staHI = 0;
	L = endHI = 1;
	queHI[0] = {1, -1};
	High.insert({1, 0});
	// Right
	R = 0;
	szLO = 1;
	queLO[0] = {0, -1};
	Low.insert({0, 0});
	pw = r = ppw = 1;
	mod = n;
	bool flag = 0;
	while(!flag)
	{
		// extend Right
		for(int i = 0, limit = szLO; i < limit; ++i)
		{
			int val = queLO[i].first + pw;
			if(val >= n)
				val -= n;
			if(!Low.count(val)) // add 1 at left
			{
				//printf("R %d -> %d : 10^%d\n", queLO[i].first, val, R);
				queLO[szLO] = {val, R};
				Low.insert({val, szLO});
				++szLO;
			}
		}
		//printf("R=%d, %d, %d\n", R, (int)Low.size(), szLO);
		++R;
		pw = 10LL * pw % n;
		int dt = std::__gcd(10, mod);
		r *= dt;
		ppw = (LL)(10 / dt) * ppw % n;
		mod /= dt;
		if(dt > 1)
		{
			std::unordered_map<int, int>(std::min(mod, (int)High.size())).swap(tmp);
			for(auto &it : High)
			{
				int val = it.first % mod, idx = it.second;
				if(!tmp.count(val))
					tmp.insert({val, idx});
				else if(tmp[val] > idx)
					tmp[val] = idx;
			}
			High.swap(tmp);
		}
		int invp = mod_inv(ppw, mod);
		for(int i = 0; i < szLO; ++i)
		{
			int val = queLO[i].first;
			if(val)
				val = n - val;
			if(val % r)
				continue;
			int wan = (LL)(val / r) * invp % mod;
			if(High.count(wan))
			{
				if(!flag)
				{
					ans = {High[wan], i};
					flag = 1;
				}
				else
				{
					std::pair<int, int> state = {High[wan], i};
					if(ans > state)
						ans = state;
				}
			}
		}
		if(flag)
			break;
		// extend Left
		int endT = endHI;
		for( ; staHI < endHI; ++staHI)
		{
			int val = 10LL * queHI[staHI].first % n, val2 = val % mod;
			if(!High.count(val2)) // add 0
			{
				//printf("L %d -> %d : +0\n", queHI[staHI].first, val);
				queHI[endT] = {val, staHI};
				High.insert({val2, endT});
				++endT;
			}
			if(++val >= n)
				val -= n;
			if(++val2 >= mod)
				val2 -= mod;
			if(!High.count(val2)) // add 1
			{
				//printf("L %d -> %d : +1\n", queHI[staHI].first, val);
				queHI[endT] = {val, staHI};
				High.insert({val2, endT});
				++endT;
			}
		}
		//printf("L=%d, %d, [%d, %d](%d)\n", L, (int)High.size(), staHI, endHI, endT);
		++L;
		for( ; endHI < endT; ++endHI)
		{
			int val = (LL)pw * queHI[endHI].first % n;
			if(val)
				val = n - val;
			if(Low.count(val))
			{
				ans = {endHI, Low[val]};
				flag = 1;
				break;
			}
		}
	}
	print();
	return 0;
}
