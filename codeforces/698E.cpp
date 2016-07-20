#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 1001;
const int mons[][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
int ss, mm, hh, wk, dd, mt, t;
LL val, year, cyear;
int mon, day, vs, vm, vh, vwk;
int cmon, cday, cs, cm, ch, cwk;
inline bool spyear(int year)
{
	return year % 400 == 0 || year % 4 == 0 && year % 100 != 0;
}
inline bool c_valid(int lim)
{
	if(year != cyear || lim == 1)
		return year < cyear;
	if(mon != cmon || lim == 2)
		return mon < cmon;
	if(day != cday || lim == 3)
		return day < cday;
	if(vh != ch || lim == 4)
		return vh < ch;
	if(vm != cm || lim == 5)
		return vm < cm;
	return vs < cs;
}
inline bool isIns(int lim)
{
	int ls = ss == -1 ? 59 : ss;
	if(lim == 1)
		return vs < ls;
	int lm = mm == -1 ? 59 : mm;
	if(lim == 2)
		return vm < lm || vm == lm && vs < ls;
	int lh = hh == -1 ? 23 : hh;
	return vh < lh || vh == lh && (vm < lm || vm == lm && vs < ls);
}
void val_init()
{
	// calc (ss, mm, hh)
	vs = val % 60;
	val /= 60;
	vm = val % 60;
	val /= 60;
	vh = val % 24;
	val /= 24;
	// calc (week, year)
	vwk = (3 + val) % 7 + 1;
	if(val <= 10957)
	{
		year = 1970;
		for(int days; (days = spyear(year) ? 366 : 365) < val; ++year, val -= days);
	}
	else
	{
		val -= 10957;
		year = 2000;
		if(val >= 366)
		{
			++year;
			val -= 366;
			year += val / 146097 * 400;
			val %= 146097;
			if(val / 36524 == 4)
			{
				year += 399;
				val = 365;
			}
			else
			{
				year += val / 36524 * 100;
				val %= 36524;
				year += val / 1461 * 4;
				val %= 1461;
				if(val / 365 == 4)
				{
					year += 3;
					val = 365;
				}
				else
				{
					year += val / 365;
					val %= 365;
				}
			}
		}
	}
	// calc (mm, dd)
	const int *month = mons[spyear(year)];
	for(int i = 1; i <= 12; ++i)
		if(val >= month[i])
			val -= month[i];
		else
		{
			mon = i;
			day = (int)val + 1;
			break;
		}
	//printf("current time:%9I64d-%02d-%02d %02d:%02d:%02d (%d)\n", year, mon, day, vh, vm, vs, vwk);
}
void val_calc()
{
	//printf("future time :%9I64d-%02d-%02d %02d:%02d:%02d (%d)\n", cyear, cmon, cday, ch, cm, cs, wk == -1 ? -1 : cwk);
	LL year, tmp;
	val = 0;
	for(year = 1970; year + 1 <= cyear && year <= 2000; val += spyear(year++) ? 366 : 365);
	tmp = (cyear - year) / 400;
	val += tmp * 146097;
	year += tmp * 400;
	tmp = (cyear - year) / 100;
	val += tmp * 36524;
	year += tmp * 100;
	tmp = (cyear - year) / 4;
	val += tmp * 1461;
	year += tmp * 4;
	val += (cyear - year) * 365;
	const int *month = mons[spyear(cyear)];
	for(int mon = 1; mon + 1 <= cmon; val += month[mon++]);
	val += cday - 1;
	val = val * 24 + ch;
	val = val * 60 + cm;
	val = val * 60 + cs;
}
void solve()
{
	if(wk == -1)
	{
		cyear = year;
		if(mt == -1)
			cmon = mon;
		else
		{
			cmon = mt;
			if(mt < mon)
				++cyear;
		}
		if(dd == -1)
			cday = c_valid(2) ? 1 : day;
		else
		{
			while(mons[spyear(cyear)][cmon] < dd)
			{
				if(mt == -1)
				{
					if(++cmon > 12)
					{
						cmon = 1;
						++cyear;
					}
				}
				else
					++cyear;
			}
			cday = dd;
		}
		if(!c_valid(3) && !(year == cyear && mon == cmon && day == cday && isIns(3)))
		{
			if(dd == -1)
			{
				if(++cday > mons[spyear(cyear)][cmon])
				{
					cday = 1;
					if(mt == -1)
					{
						if(++cmon > 12)
						{
							cmon = 1;
							++cyear;
						}
					}
					else
						++cyear;
				}
			}
			else
			{
				do
				{
					if(mt == -1)
					{
						if(++cmon > 12)
						{
							cmon = 1;
							++cyear;
						}
					}
					else
						++cyear;
				} while(mons[spyear(cyear)][cmon] < cday);
			}
		}
		bool flag = c_valid(3);
		ch = hh == -1 ? (flag ? 0 : (isIns(2) ? vh : vh + 1)) : hh;
		flag |= ch > vh;
		cm = mm == -1 ? (flag ? 0 : (isIns(1) ? vm : vm + 1)) : mm;
		flag |= cm > vm;
		cs = ss == -1 ? (flag ? 0 : vs + 1) : ss;
	}
	else
	{
		cyear = year;
		if(mt == -1 || mt == mon)
		{
			cmon = mon;
			if(dd == -1 || day < dd && dd < mons[spyear(cyear)][cmon])
			{
				cday = dd == -1 ? day : dd;
				cwk = (vwk + cday - day - 1) % 7 + 1;
				if(dd == -1)
				{
					for( ; cday < mons[spyear(cyear)][cmon] && cwk != wk; ++cday, cwk = cwk % 7 + 1);
					if(!c_valid(3) && !(year == cyear && mon == cmon && day == cday && isIns(3)) && cday < mons[spyear(cyear)][cmon])
						for(++cday, cwk = cwk % 7 + 1; cday < mons[spyear(cyear)][cmon] && cwk != wk; ++cday, cwk = cwk % 7 + 1);
				}
				if(cwk == wk && (c_valid(3) || year == cyear && mon == cmon && day == cday && isIns(3)))
				{
					bool flag = c_valid(3);
					ch = hh == -1 ? (flag ? 0 : (isIns(2) ? vh : vh + 1)) : hh;
					flag |= ch > vh;
					cm = mm == -1 ? (flag ? 0 : (isIns(1) ? vm : vm + 1)) : mm;
					flag |= cm > vm;
					cs = ss == -1 ? (flag ? 0 : vs + 1) : ss;
				}
				else
					cday = 0;
			}
			else
				cday = 0;
		}
		else
		{
			cmon = mon;
			cwk = (vwk - day) % 7 + 1;
			if(cwk < 1)
				cwk += 7;
			cday = 1;
			while(cmon != mt)
			{
				cwk = (cwk + mons[spyear(cyear)][cmon] - 1) % 7 + 1;
				if(++cmon > 12)
				{
					cmon = 1;
					++cyear;
				}
			}
			ch = -1;
		}
		if(cday == 0 || ch == -1)
		{
			if(mt == -1 || mt == mon)
			{
				cwk = (vwk - day) % 7 + 1;
				if(cwk < 1)
					cwk += 7;
				cday = 1;
				if(mt == -1)
				{
					cwk = (cwk + mons[spyear(cyear)][cmon] - 1) % 7 + 1;
					if(++cmon > 12)
					{
						cmon = 1;
						++cyear;
					}
				}
				else
				{
					cwk = (cwk + (spyear(cmon <= 2 ? cyear : cyear + 1) ? 366 : 365) - 1) % 7 + 1;
					++cyear;
				}
			}
			while(1)
			{
				if(dd == -1)
					for( ; cwk != wk; ++cday, cwk = cwk % 7 + 1);
				else
				{
					cday = dd;
					cwk = (cwk + cday - 1 - 1) % 7 + 1;
				}
				if(cwk == wk)
					break;
				cwk = (cwk - cday) % 7 + 1;
				if(cwk < 1)
					cwk += 7;
				cday = 1;
				if(mt == -1)
				{
					cwk = (cwk + mons[spyear(cyear)][cmon] - 1) % 7 + 1;
					if(++cmon > 12)
					{
						cmon = 1;
						++cyear;
					}
				}
				else
				{
					cwk = (cwk + (spyear(cmon <= 2 ? cyear : cyear + 1) ? 366 : 365) - 1) % 7 + 1;
					++cyear;
				}
			}
			ch = hh == -1 ? 0 : hh;
			cm = mm == -1 ? 0 : mm;
			cs = ss == -1 ? 0 : ss;
		}
	}
}
int main()
{
	scanf("%d%d%d%d%d%d%d", &ss, &mm, &hh, &wk, &dd, &mt, &t);
	while(t--)
	{
		scanf("%I64d", &val);
		val_init();
		bool flag = wk == -1 || dd == -1;
		if(flag)
		{
			solve();
			val_calc();
		}
		else
		{
			int tmp = wk;
			wk = -1;
			solve();
			wk = tmp;
			val_calc();
			LL val2 = val;
			tmp = dd;
			dd = -1;
			solve();
			dd = tmp;
			val_calc();
			if(val2 < val)
				val = val2;
		}
		printf("%I64d\n", val);
	}
	return 0;
}
