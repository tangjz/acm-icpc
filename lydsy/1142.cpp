#include <stdio.h>
#include <cstring>
namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		bool sign = 0;
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		ch == '-' ? sign = 1, x = 0 : x = ch - '0';
		for( ; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
		x = sign ? -x : x;
	}
	#undef BUF_SIZE
};
using namespace fastIO;
const int maxn = 1001, delta = 1000000, maxs = delta << 1 | 1;
int t, n, m, row[maxn], col[maxn], idx[maxs];
int main()
{
	read(t);
	while(t--)
	{
		read(n), read(m);
		bool chk = 1;
		memset(row, -1, n * sizeof(int));
		memset(col, -1, m * sizeof(int));
		memset(idx, -1, sizeof idx);
		for(int i = 0; i < n * m; ++i)
		{
			int x;
			read(x);
			idx[x += delta] = i;
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				int x;
				read(x);
				if(chk)
					chk &= idx[x += delta] != -1;
				if(chk)
				{
					int r = idx[x] / m, c = idx[x] % m;
					chk &= row[i] == -1 || row[i] == r;
					chk &= col[j] == -1 || col[j] == c;
					row[i] = r;
					col[j] = c;
				}
			}
		puts(chk ? "TAK" : "NIE");
	}
	return 0;
}
