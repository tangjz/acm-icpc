#include <cstdio>
#include <cstring>
const int maxn = 233;
const char *ope = "{([", *clo = "})]";
char str[maxn], out[maxn];
int len, posL, posR, tlen;
void solve(int L, int R) // [L, R)
{
	if(L >= R)
		return;
	int pL[3], pR[3];
	for(int i = L; i < R; ++i)
	{
		int pos = -1;
		for(int j = 0; j < 3; ++j)
			if(str[i] == ope[j])
				pos = j;
		if(pos == -1)
			continue;
		int end = i + 1;
		for( ; end < R; ++end)
			if(str[end] == clo[pos])
				break;
		pL[pos] = i + 1;
		pR[pos] = end;
		i = end;
	}
	str[pR[0]] = '\0';
	strcat(out, str + pL[0]);
	tlen += pR[0] - pL[0];
	out[tlen++] = ' ';
	str[pR[1]] = '\0';
	strcat(out, str + pL[1]);
	tlen += pR[1] - pL[1];
	out[tlen++] = ' ';
	str[pR[2]] = '\0';
	strcat(out, str + pL[2]);
	tlen += pR[2] - pL[2];
}
int main()
{
	gets(str);
	len = strlen(str);
	posL = len;
	for(int i = 0; i < len; ++i)
		if(str[i] == ',')
		{
			posL = i;
			break;
		}
	posR = len;
	for(int i = posL + 1; i < len; ++i)
		if(str[i] == '{' || str[i] == '(' || str[i] == '[')
		{
			posR = i;
			break;
		}
	solve(0, posL);
	if(posL < len)
	{
		char tmp = str[posR];
		str[posR] = '\0';
		strcat(out, str + posL);
		str[posR] = tmp;
		tlen += posR - posL;
		solve(posR, len);
	}
	out[tlen] = '\0';
	for(int i = 0; i < tlen; ++i)
		if(out[i] >= 'A' && out[i] <= 'Z')
			out[i] += 'a' - 'A';
	out[0] -= 'a' - 'A';
	puts(out);
	return 0;
}
