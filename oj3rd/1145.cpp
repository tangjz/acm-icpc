#include <cstdio>
const char *op = "+-*/";
int stack[7], top;
char str[5], exa[8];
bool vis[4], ans[10000];
int GetValue()
{
	top = -1;
	for(int i = 0; i < 7; ++i)
		if(exa[i] >= '0' && exa[i] <= '9')
			stack[++top] = exa[i] - '0';
		else
		{
			switch(exa[i])
			{
				case '+': stack[top - 1] += stack[top]; break;
				case '-': stack[top - 1] -= stack[top]; break;
				case '*': stack[top - 1] *= stack[top]; break;
				case '/': if(!stack[top]) return 0; stack[top - 1] /= stack[top];
			}
			--top;
		}
	return top ? 0 : stack[top];
}
bool dfs(int dep, int cnum, int cop)
{
	if(dep == 7)
		return GetValue() == 10;
	if(cnum < 4)
		for(int i = 0; i < 4; ++i)
			if(!vis[i])
			{
				exa[dep] = str[i];
				vis[i] = 1;
				if(dfs(dep + 1, cnum + 1, cop))
					return 1;
				vis[i] = 0;
			}
	if(cop < 3 && cnum > cop + 1)
		for(int i = 0; i < 4; ++i)
		{
			exa[dep] = op[i];
			if(dfs(dep + 1, cnum, cop + 1))
				return 1;
		}
	return 0;
}
void swap(char &x, char &y)
{
	char t = x;
	x = y;
	y = t;
}
int main()
{
	for(int i = 0; i < 10000; ++i)
	{
		sprintf(str, "%04d", i);
		for(int j = 0; j < 4; ++j)
		{
			int p = j;
			for(int k = j + 1; k < 4; ++k)
				if(str[j] > str[k])
					p = k;
			if(j != p)
				swap(str[j], str[p]);
		}
		int tmp;
		sscanf(str, "%d", &tmp);
		if(tmp == i)
		{
			vis[0] = vis[1] = vis[2] = vis[3] = 0;
			ans[i] = dfs(0, 0, 0);
		}
		else
			ans[i] = ans[tmp];
	}
	while(scanf("%s", str) != EOF)
	{
		int tmp;
		sscanf(str, "%d", &tmp);
		puts(ans[tmp] ? "Yes" : "No");
	}
	return 0;
}
