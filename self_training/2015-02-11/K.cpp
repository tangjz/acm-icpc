#include <stack>
#include <queue>
#include <cstdio>
using namespace std;
int n, valid1, valid2, valid3;
stack<int> A;
queue<int> B;
priority_queue<int> C;
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		while(!A.empty())
			A.pop();
		valid1 = 1;
		while(!B.empty())
			B.pop();
		valid2 = 1;
		while(!C.empty())
			C.pop();
		valid3 = 1;
		while(n--)
		{
			int op, x;
			scanf("%d%d", &op, &x);
			if(op == 1)
			{
				if(valid1)
					A.push(x);
				if(valid2)
					B.push(x);
				if(valid3)
					C.push(x);
			}
			else
			{
				if(valid1)
				{
					if(A.empty() || A.top() != x)
						valid1 = 0;
					else
						A.pop();
				}
				if(valid2)
				{
					if(B.empty() || B.front() != x)
						valid2 = 0;
					else
						B.pop();
				}
				if(valid3)
				{
					if(C.empty() || C.top() != x)
						valid3 = 0;
					else
						C.pop();
				}
			}
		}
		if(valid1 + valid2 + valid3 > 1)
			puts("not sure");
		else if(valid1)
			puts("stack");
		else if(valid2)
			puts("queue");
		else if(valid3)
			puts("priority queue");
		else
			puts("impossible");
	}
	return 0;
}
