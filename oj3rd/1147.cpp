#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
string str;
vector<int> num;
int main()
{
	ios::sync_with_stdio(0);
	while(getline(cin, str))
	{
		int temp;
		stringstream tmp(str);
		num.clear();
		while(tmp >> temp)
			num.push_back(temp);
		sort(num.begin(), num.end(), greater<int>());
		for(vector<int>::iterator it = num.begin(), jt = num.end(); ; )
		{
			cout << *it;
			++it;
			if(it == jt)
				break;
			else
				cout << ' ';
		}
		cout << endl;
	}
	return 0;
}
