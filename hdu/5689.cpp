#include <map>
#include <string>
#include <stdio.h>
#include <algorithm>
const int maxn = 1001, maxs = 1 << 16 | 1, maxv = 10000;
int tot;
std::map<std::string, int> Hash;
int getId(char *s)
{
	std::string tmp = s;
	return Hash.count(tmp) ? Hash[tmp] : Hash[tmp] = tot++;
}
struct Node
{
	bool isEmpty;
	std::map<int, std::pair<int, int> > Equ;
	void insert(int idx, int L, int R)
	{
		if(isEmpty)
			return;
		std::pair<int, int> tmp = Equ.count(idx) ? Equ[idx] : std::make_pair(-maxv, maxv);
		tmp.first = std::max(tmp.first, L);
		tmp.second = std::min(tmp.second, R);
		if(tmp.first <= tmp.second)
			Equ[idx] = tmp;
		else
		{
			std::map<int, std::pair<int, int> >().swap(Equ);
			isEmpty = 1;
		}
	}
	bool isIns(Node &t)
	{
		if(isEmpty || t.isEmpty)
			return 0;
		for(std::map<int, std::pair<int, int> >::iterator it = Equ.begin(), jt = t.Equ.begin(); it != Equ.end() && jt != t.Equ.end() ; ++it, ++jt)
			if(it -> first != jt -> first)
				it -> first < jt -> first ? ++it : ++jt;
			else
			{
				std::pair<int, int> a = it -> second, b = jt -> second;
				if(std::max(a.first, b.first) > std::min(a.second, b.second))
					return 0;
			}
		return 1;
	}
};
int n;
Node e[maxn];
char str[maxs];
int main()
{
	scanf("%d ", &n);
	for(int i = 0; i < n; ++i)
	{
		gets(str);
		for(int j = 0, k; str[j]; ++j)
		{
			char ch;
			for( ; str[j] == ' '; ++j);
			for(k = j + 1; str[k] && str[k] != ' ' && str[k] != '<' && str[k] != '>' && str[k] != '='; ++k);
			ch = str[k];
			str[k] = '\0';
			int idx = getId(str + j);
			str[k] = ch;
			for(j = k; str[j] == ' '; ++j);
			bool less = str[j] == '<', greater = str[j] == '>', equal = str[j] == '=' || str[j + 1] == '=';
			for(k = j + 1; str[k] && str[k] != ' ' && !(str[k] >= '0' && str[k] <= '9') && str[k] != '-'; ++k);
			for(j = k; str[j] == ' '; ++j);
			for(k = j + 1; str[k] && str[k] != ' ' && str[k] != ','; ++k);
			ch = str[k];
			str[k] = '\0';
			int value;
			sscanf(str + j, "%d", &value);
			if(less)
				e[i].insert(idx, -maxv, value - (!equal));
			else if(greater)
				e[i].insert(idx, value + (!equal), maxv);
			else
				e[i].insert(idx, value, value);
			str[k] = ch;
			for(j = k; str[j] == ' '; ++j);
			if(str[j] != ',')
				break;
		}
		bool flag = 0;
		for(int j = 0; j < i; ++j)
			if(e[i].isIns(e[j]))
			{
				if(flag)
					putchar(' ');
				else
					flag = 1;
				printf("%d", j + 1);
			}
		if(flag)
			putchar('\n');
		else
			puts("unique");
	}
	return 0;
}
