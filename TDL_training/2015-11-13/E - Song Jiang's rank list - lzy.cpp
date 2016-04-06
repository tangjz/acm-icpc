#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int n,m,x[209],y[209];
pair<int,string> a[209];
string q;


int main()
{
    while (cin>>n && n)
    {
    	for (int i=0;i<n;++i) cin>>a[i].second>>a[i].first;
    	for (int i=0;i<n;++i) a[i].first=-a[i].first;
    	sort(a,a+n);
    	for (int i=0;i<n;++i) a[i].first=-a[i].first;
    	for (int i=0;i<n;++i) cout<<a[i].second<<' '<<a[i].first<<endl;
    	cin>>m;
    	x[0]=1;
    	y[0]=1;
    	for (int i=1;i<n;++i)
    	{
    		if (a[i].first==a[i-1].first)
    		{
    			y[i]=y[i-1]+1;
    		}
    		else
    		{
    			y[i]=1;
    		}
    	}
    	for (int i=0;i<n;++i)
		{
			int s=1;
			for (int j=0;a[j].first>a[i].first;++j) ++s;
			x[i]=s;
		}
    	while (m--)
    	{
    		cin>>q;
    		for (int i=0;i<n;++i) if (a[i].second==q)
    		{
    			cout<<x[i];
    			if (y[i]!=1) cout<<' '<<y[i];
    			cout<<endl;
    			break;
    		}
    	}
    }
    return 0;
}
