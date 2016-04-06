#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

string a,b;
map<string,int> g;
map<string,string> f;

int c,l,m,n;
char s[64],t[64];
char str[32][8];

void init()
{
	for (int i=2;i<=30;++i) sprintf(str[i],"%d",i);
}
string abbr(char s[],int l)
{
	string ret;
	return ret+s[0]+str[l-2]+s[l-1];
}
int isAbbr(char s[],int l)
{
	if (l<3) return 0;
	if (!(isalpha(s[0]) && isalpha(s[l-1]))) return 0;
	int ret=0;
	for (int i=1;i<l-1;++i)
	{
		if (isdigit(s[i])) ret=ret*10+s[i]-'0';
		else return 0;
	}
	if (ret<2 || ret>30) return 0;
	else return ret;
}
bool isWord(char s[],int l)
{
	if (l<4) return false;
	for (int i=0;i<l;++i) if (!isalpha(s[i])) return false;
	return true;
}
string cut(char s[],int l)
{
	string ret;
	for (int i=1;i<l-1;++i) ret+=s[i];
	return ret;
}

int main()
{
	init();
	while ((c=getchar())!=EOF)
	{
		if (isalpha(c))
		{
			s[l++]=tolower(c);
			t[m++]=c;
		}
		else if (isdigit(c))
		{
			s[l++]=c;
			t[m++]=c;
		}
		else
		{
			s[l]='\0';
			t[m]='\0';
			if ((n=isAbbr(s,l)))
			{
				a.clear();
				a+=s[0];
				a+=str[n];
				a+=s[l-1];
				//cout<<"a: "<<a<<endl;
				if (g.count(a) && g[a]==1)
				{
					b=f[a];
					if (isupper(t[l-1]))
					{
						transform(b.begin(),b.end(),b.begin(),::toupper);
					}
					cout<<t[0]<<b<<t[l-1];
				}
				else cout<<t;
			}
			else cout<<t;
			if (isWord(s,l))
			{
				a=abbr(s,l);
				if (g[a]==0)
				{
					++g[a];
					f[a]=cut(s,l);
				}
				else if (f[a]!=cut(s,l))
				{
					++g[a];
				}
			}
			l=0;
			m=0;
			putchar(c);
		}
	}
	return 0;
}
