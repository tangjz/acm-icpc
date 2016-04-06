#include <iostream>
#include <string>

using namespace std;

typedef unsigned u32;

int T,n,m;
string s,t;
string f[26];

bool dfs(u32 i,u32 j)
{
	if (i==s.length() && j==t.length()) return true;
	if (i==s.length() || j==t.length()) return false;
	for (int k=1;k<=m&&j+k<=t.length();++k)
	{
		string tmp=f[s[i]-'a'];
		if (f[s[i]-'a'].empty())
		{
			f[s[i]-'a']=t.substr(j,k);
		}
		if (f[s[i]-'a']==t.substr(j,k))
		{
			if (dfs(i+1,j+k)) return true;
		}
		f[s[i]-'a']=tmp;
	}
	return false;
}
int main()
{
	cin>>T;
	while (T--)
	{
		for (auto &i:f) i.clear();
		cin>>m>>s>>t;
		cout<<dfs(0,0)<<endl;
	}
	return 0;
}
