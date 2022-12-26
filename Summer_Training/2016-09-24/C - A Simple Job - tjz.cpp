#include <map>
#include <string>
#include <stdio.h>
#include <cstring>
using namespace std;
const int maxs = 510 * 51;
map<string, int> Hash;
int len;
char str[maxs];
int main()
{
	while(gets(str))
	{
		len = strlen(str);
		str[len++] = '\n';
		str[len] = '\0';
		while(gets(str + len) && strcmp(str + len, "####"))
		{
			len += strlen(str + len);
			str[len++] = '\n';
			str[len] = '\0';
		}
		int tlen = 0;
		for(int i = 0; i < len; ++i)
			if(str[i] >= 'a' && str[i] <= 'z')
				str[tlen++] = str[i];
			else if(str[i] == ' ')
			{
				if(tlen && str[tlen - 1] >= 'a' && str[tlen - 1] <= 'z')
					str[tlen++] = ' ';
			}
			else
			{
				if(tlen)
				{
					if(str[tlen - 1] >= 'a' && str[tlen - 1] <= 'z')
						str[tlen++] = '#';
					else if(str[tlen - 1] == ' ')
						str[tlen - 1] = '#';
				}
			}
		str[tlen] = '\0';
		// puts(str);
		len = tlen;
		map<string, int>().swap(Hash);
		for(int i = 0, p1 = -1, p2 = -1; i < len; ++i)
			if(str[i] < 'a' || str[i] > 'z')
			{
				if(p2 != -1 && str[p2] == ' ')
				{
					char ch = str[i];
					str[i] = '\0';
					++Hash[(string)(str + p1 + 1)];
					str[i] = ch;
				}
				p1 = p2;
				p2 = i;
			}
		int cnt = 0;
		map<string, int>::iterator ans;
		for(map<string, int>::iterator it = Hash.begin(); it != Hash.end(); ++it)
			if(cnt < it -> second)
			{
				cnt = it -> second;
				ans = it;
			}
		printf("%s:%d\n", (ans -> first).c_str(), cnt);
	}
	return 0;
}
