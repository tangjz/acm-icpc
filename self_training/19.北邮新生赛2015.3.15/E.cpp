#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 15;
const char *pai = "3456789TJQKA2XY";
int trans[256];
char yours[25], mine[25];
int yid, yB, yK1, yC, yK2, yS[maxn];
int msz[5], mcnt[maxn], mx[5], mS[maxn];
//			mind mx[4] include XY
void judge()
{
	int Ssz = 0, S[25] = {};
	int Csz = 0, C[maxn] = {};
	for(int i = 0; yours[i]; ++i)
		S[Ssz++] = trans[(int)yours[i]];
	sort(S, S + Ssz);
	for(int i = 0; i < Ssz; ++i)
	{
		if(!i || S[i - 1] != S[i])
			++Csz;
		++C[Csz - 1];
	}
	unique(S, S + Ssz); // Ssz = Csz;
	if(Ssz == 2 && Csz == 2 && S[0] == trans[(int)'X'] && S[1] == trans[(int)'Y']
	|| Ssz == 4 && Csz == 1)
	{
		yid = 0;
		yB = S[0];
		return;
	}
	if(Ssz == 1)
	{
		yid = 1;
		yB = S[0];
		return;
	}
	if(Ssz == 2 && Csz == 1)
	{
		yid = 2;
		yB = S[0];
		return;
	}
	if(Ssz == 3 && Csz ==1)
	{
		yid = 3;
		yB = S[0];
		return;
	}
	if((Ssz == 4 || Ssz == 5) && Csz == 2)
	{
		if(C[1] == 3)
		{
			swap(S[0], S[1]);
			swap(C[0], C[1]);
		}
		yid = 4;
		yB = S[0];
		yC = S[1];
		yK2 = C[1];
		return;
	}
	if(Ssz == Csz && Csz == S[Csz - 1] - S[0] + 1)
	{
		yid = 5;
		yB = S[0];
		yK1 = Csz;
		return;
	}
	if(Ssz == Csz * 2 && Csz == S[Csz - 1] - S[0] + 1)
	{
		bool flag = 1;
		for(int i = 0; i < Csz && flag; ++i)
			flag &= C[i] == 2;
		if(flag)
		{
			yid = 6;
			yB = S[0];
			yK1 = Csz;
			return;
		}
	}
	if(Ssz == Csz * 3 && Csz == S[Csz - 1] - S[0] + 1)
	{
		bool flag = 1;
		for(int i = 0; i < Csz && flag; ++i)
			flag &= C[i] == 2;
		if(flag)
		{
			yid = 7;
			yB = S[0];
			yK1 = Csz;
			return;
		}
	}
	if(Ssz % 4 == 0 && Csz * 4 == Ssz * 2)
	{
		int tmp1 = 0, tmp2 = 0, Max = -1, Min = 233;
		for(int i = 0; i < Csz; ++i)
			if(C[i] == 3)
			{
				++tmp1;
				if(S[i] > Max)
					Max = S[i];
				if(S[i] < Min)
					Min = S[i];
			}
			else if(C[i] == 1)
				yS[tmp2++] = S[i];
		if(2 * tmp1 == Csz && tmp1 == Max - Min + 1 && tmp1 == tmp2)
		{
			yid = 8;
			yB = Min;
			yK1 = tmp1;
			yK2 = 1;
			return;
		}
	}
	if(Ssz % 5 == 0 && Csz * 5 == Ssz * 2)
	{
		int tmp1 = 0, tmp2 = 0, Max = -1, Min = 233;
		for(int i = 0; i < Csz; ++i)
			if(C[i] == 3)
			{
				++tmp1;
				if(S[i] > Max)
					Max = S[i];
				if(S[i] < Min)
					Min = S[i];
			}
			else if(C[i] == 2)
				yS[tmp2++] = S[i];
		if(2 * tmp1 == Csz && tmp1 == Max - Min + 1 && tmp1 == tmp2)
		{
			yid = 8;
			yB = Min;
			yK1 = tmp1;
			yK2 = 2;
			return;
		}
	}
	if(Ssz > 4)
	{
		int tmp = 0;
		for(int i = 0; i < Csz; ++i)
			if(C[i] == 4)
				++tmp;
		if(tmp == 1)
		{
			yid = 9;
			return;
		}
	}
	yid = -1;
	puts("invalid");
}
void init()
{
	memset(msz, 0, sizeof msz);
	memset(mcnt, 0, sizeof mcnt);
	memset(mx, -1, sizeof mx);
	for(int i = 0; mine[i]; ++i)
	{
		if(trans[(int)mine[i]] == -1)
		{
			puts("invalid");
			continue;
		}
		++mcnt[trans[(int)mine[i]]];
	}
	for(int i = 0; i < maxn; ++i)
	{
		++msz[mcnt[i]];
		mx[mcnt[i]] = i;
	}
	for(int i = 3; i >= 1; --i)
	{
		msz[i] += msz[i + 1];
		if(mx[i] < mx[i + 1])
			mx[i] = mx[i + 1];
	}
	if(mcnt[trans[(int)'X']] && mcnt[trans[(int)'Y']])
		mx[4] = trans[(int)'X'];
}
bool check()
{
	if(yid == 0)
		return mx[4] > yB;
	if(mx[4] != -1)
		return 1;
	switch(yid)
	{
		case 1: return mx[1] > yB;
		case 2: return mx[2] > yB;
		case 3: return mx[3] > yB;
		case 4:
			if(mx[3] != yB || msz[yK2] == 1)
				return mx[3] > yB && msz[yK2] > 1;
			mcnt[mx[3]] = 0;
			for(int i = maxn - 1; i >= 0; --i)
				if(mcnt[i] >= yK2)
					return i > yC;
			return 0;
		case 5:
			for(int i = maxn - 4, j = 0; i >= 0; --i)
			{
				j = mcnt[i] >= 1 ? j + 1 : 0;
				if(j == yK1)
					return i > yB;
			}
			return 0;
		case 6:
			for(int i = maxn - 4, j = 0; i >= 0; --i)
			{
				j = mcnt[i] >= 2 ? j + 1 : 0;
				if(j == yK1)
					return i > yB;
			}
			return 0;
		case 7:
			for(int i = maxn - 4, j = 0; i >= 0; --i)
			{
				j = mcnt[i] >= 3 ? j + 1 : 0;
				if(j == yK1)
					return i > yB;
			}
			return 0;
		case 8:
			for(int i = maxn - 4, j = 0; i >= 0; --i)
			{
				j = mcnt[i] >= 3 ? j + 1 : 0;
				if(j == yK1)
				{
					if(i < yB)
						return 0;
					for(int t = 0; t < yK1; ++t)
						mcnt[i + t] = 0;
					int tmp = yK1;
					for(int t = maxn - 1; t >= 0; --t)
						if(tmp > 0 && mcnt[t] >= yK2)
							mS[--tmp] = t;
					if(tmp > 0)
						return 0;
					if(i > yB)
						return 1;
					for(int t = yK1 - 1; t >= 0; --t)
						if(yS[t] != mS[t])
							return yS[t] < mS[t];
					return 0;
				}
			}
		case 9: return 0;
	}
	return 0;
}
int main()
{
	memset(trans, -1, sizeof trans);
	for(int i = 0; i < maxn; ++i)
		trans[(int)pai[i]] = i;
	while(scanf("%s%s", yours, mine) == 2)
	{
		judge(); // judge yours
		init(); // init mine
		puts(check() ? "Yes" : "No"); // check Yes or No
	}
	return 0;
}
