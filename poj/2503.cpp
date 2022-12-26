#include <map>
#include <cstdio>
#include <string>
using namespace std;
map<string, string> Hash;
char tmp[100001];
string tmp1, tmp2;
int main()
{
	while(gets(tmp))
	{
		tmp1 = tmp;
		string::size_type pos = tmp1.find(' ');
		if(pos == string::npos)
			break;
		tmp2 = tmp1.substr(pos + 1);
		tmp1 = tmp1.substr(0, pos);
		Hash[tmp2] = tmp1;
	}
	while(scanf("%s", tmp) != EOF)
		if(Hash.find((string)tmp) != Hash.end())
			printf("%s\n", Hash[(string)tmp].c_str());
		else
			puts("eh");
	return 0;
}
