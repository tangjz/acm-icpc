#include <map>
#include <cctype>
#include <string>
#include <stdio.h>
#include <cstring>
using namespace std;
const int maxn = 110, maxs = 110;
const char *oper = "+-*/";
int n, len[maxn], F[maxn][maxs][maxs];
char str[maxn][maxs], buf[maxs];
map<string, int> idx;
int f(int id, int L, int R) // state of str[id][L : R]
{
	if(L >= R)
		return 0;
	int &ret = F[id][L][R];
	if(ret != -1)
		return ret;
	if(str[id][L] == '(')
	{
		int pos, cnt = 1;
		for(pos = L + 1; pos < R; ++pos)
		{
			if(str[id][pos] == '(')
				++cnt;
			else if(str[id][pos] == ')')
				--cnt;
			if(!cnt)
				break;
		}
		if(pos == R - 1)
			return ret = f(id, L + 1, R - 1) != 1 ? 0 : 1;
	}
	int pos, cnt = 0;
	for(pos = R - 1; pos >= L; --pos)
	{
		int i;
		for(i = 0; oper[i] && oper[i] != str[id][pos]; ++i);
		if(str[id][pos] == ')')
			++cnt;
		else if(str[id][pos] == '(')
			--cnt;
		if(!cnt && oper[i])
			break;
	}
	if(pos < L)
	{
		char ch = str[id][R];
		str[id][R] = '\0';
		string msk = str[id] + L;
		str[id][R] = ch;
		if(idx.count(msk))
		{
			int nid = idx[msk];
			return ret = f(nid, 0, len[nid]);
		}
		return ret = 0;
	}
	if(str[id][pos] == '*' || str[id][pos] == '/')
	{
		int pos2, cnt = 0;
		for(pos2 = pos - 1; pos2 >= L; --pos2)
		{
			int i = 0;
			for(i = 0; i < 2 && oper[i] != str[id][pos2]; ++i);
			if(str[id][pos2] == ')')
				++cnt;
			else if(str[id][pos2] == '(')
				--cnt;
			if(!cnt && i < 2)
				break;
		}
		if(pos2 >= L)
			pos = pos2;
	}
	int fL = f(id, L, pos), fR = f(id, pos + 1, R);
	if(fL == 1 || fR == 1)
		return ret = 1;
	switch(str[id][pos])
	{
		case '+' : return ret = 2;
		case '-' : return ret = fR == 2 ? 1 : 2;
		case '*' : return ret = fL == 2 || fR == 2 ? 1 : 3;
		case '/' : return ret = fL == 2 || fR == 2 || fR == 3 ? 1 : 3;
	}
	return ret = 1;
}
int main()
{
	scanf("%d ", &n);
	for(int i = 0; i < n; ++i)
	{
		int pos, pre;
		gets(buf);
		for(pos = 0; isspace(buf[pos]); ++pos);
		for(++pos; isspace(buf[pos]); ++pos); // #
		for( ; !isspace(buf[pos]); ++pos); // define
		for( ; isspace(buf[pos]); ++pos);
		for(pre = pos; !isspace(buf[pos]); ++pos); // name
		buf[pos] = '\0';
		idx[buf + pre] = i;
		for(++pos; buf[pos]; ++pos)
			if(!isspace(buf[pos]))
				str[i][len[i]++] = buf[pos];
		str[i][len[i]] = '\0';
	}
	{ // str[n]
		int pos;
		gets(buf);
		for(pos = 0; buf[pos]; ++pos)
			if(!isspace(buf[pos]))
				str[n][len[n]++] = buf[pos];
		str[n][len[n]] = '\0';
	}
	memset(F, -1, sizeof F);
	puts(f(n, 0, len[n]) != 1 ? "OK" : "Suspicious");
	return 0;
}
