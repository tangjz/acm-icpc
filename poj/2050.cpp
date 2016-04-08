#include <map>
#include <bitset>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxr = 1510, maxc = 88;
bitset<maxr> ZERO(0), ONE(1);
map<string, int> Hash;
int n, r, m, mark[maxr], tot;
vector<bitset<maxr> > mask;
char str[maxr][maxc];
bitset<maxr> flip(bitset<maxr> tmp)
{
	return tmp.flip();
}
void Find(string s, bool flag) // ·Ç = 1 
{
	bitset<maxr> mass(0);
	bitset<maxr> &res = Hash.find(s) != Hash.end() ? mask[Hash[s]] : ZERO;
	for(int i = 0; i < r; ++i)
		mass[mark[i]] = mass[mark[i]] | res[i];
	bool flag2 = 1;
	for(int i = 0; i < n; ++i)
		flag2 &= mass[i];
	if(!flag && mass.none() || flag && flag2)
	{
		puts("Sorry, I found nothing.\n==========");
		return;
	}
	for(int i = 0, last = -1; i < r; ++i)
		if(!flag && mass[mark[i]] && res[i] || flag && !mass[mark[i]])
		{
			if(last != -1 && last != mark[i])
				puts("----------");
			puts(str[i]);
			last = mark[i];
		}
	puts("=========="); 
}
void Find(string s, string t, bool flag) // Óë = 0 »ò = 1 
{
	bitset<maxr> mass1(0), mass2(0), mass(0);
	bitset<maxr> &res1 = Hash.find(s) != Hash.end() ? mask[Hash[s]] : ZERO;
	bitset<maxr> &res2 = Hash.find(t) != Hash.end() ? mask[Hash[t]] : ZERO;
	for(int i = 0; i < r; ++i)
	{
		mass1[mark[i]] = mass1[mark[i]] | res1[i];
		mass2[mark[i]] = mass2[mark[i]] | res2[i];
	}
	for(int i = 0; i < n; ++i)
		mass[i] = flag ? mass1[i] | mass2[i] : mass1[i] & mass2[i];
	if(mass.none())
	{
		puts("Sorry, I found nothing.\n==========");
		return;
	}
	for(int i = 0, last = -1; i < r; ++i)
		if(mass[mark[i]] && (res1[i] || res2[i]))
		{
			if(last != -1 && last != mark[i])
				puts("----------");
			puts(str[i]);
			last = mark[i];
		}
	puts("=========="); 
}
int main()
{
	char op[5], tmp[maxc << 2], tmp1[maxc], tmp2[maxc];
	scanf("%d\n", &n);
	for(int t = 0; t < n; ++t)
		while(gets(str[r]) != NULL)
		{
			if(strcmp(str[r], "**********") == 0)
				break;
			int i, j;
			for(i = 0, j = 0; str[r][i]; ++i)
				if(str[r][i] >= 'A' && str[r][i] <= 'Z')
					tmp[j++] = str[r][i] - 'A' + 'a';
				else if(str[r][i] >= 'a' && str[r][i] <= 'z')
					tmp[j++] = str[r][i];
				else if(j)
				{
					tmp[j] = '\0';
					string temp = tmp;
					if(Hash.find(temp) == Hash.end())
					{
						Hash[temp] = tot++;
						mask.push_back(ZERO);
					}
					mask[Hash[temp]][r] = 1;
					j = 0;
				}
			if(j)
			{
				tmp[j] = '\0';
				string temp = tmp;
				if(Hash.find(temp) == Hash.end())
				{
					Hash[temp] = tot++;
					mask.push_back(ZERO);
				}
				mask[Hash[temp]][r] = 1;
				j = 0;
			}
			mark[r++] = t;
		}
	scanf("%d\n", &m);
	while(m--)
	{
		gets(tmp);
		if(strncmp(tmp, "NOT ", 4) == 0)
		{
			sscanf(tmp,"%*s%s", tmp1);
			Find(tmp1, 1);
		}
		else if(strchr(tmp, ' ') == NULL)
			Find(tmp, 0);
		else
		{
			sscanf(tmp, "%s%s%s", tmp1, op, tmp2);
			if(strcmp(op, "AND") == 0)
				Find(tmp1, tmp2, 0);
			else
				Find(tmp1, tmp2, 1);
		}
	}
	return 0;
}