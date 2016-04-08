/*
 * 线段树 染色+反色 
 * 每个数拆成两个便于计算开闭区间 
 */
#include <cstdio>
#include <cstdlib>
const int n = 1 << 17;
int tot = 0, out[n][2];
struct SegmentTree
{
	SegmentTree *ch[2];
	int l, r, m;
	bool flag, Xor, color;
	SegmentTree(int l, int r) : l(l), r(r), m(l + r >> 1) { ch[0] = ch[1] = NULL; flag = 1; Xor = color = 0; }
	void update()
	{
		if(l == r) return;
		if(flag)
		{
			flag = 0;
			ch[0] -> flag	= ch[1] -> flag		= 1;
			ch[0] -> Xor	= ch[1] -> Xor		= 0;
			ch[0] -> color	= ch[1] -> color	= color;
		}
		if(Xor)
		{
			Xor = 0;
			ch[0] -> Xor ^= 1;
			ch[1] -> Xor ^= 1;
		}
	}
	void fill(const int s, const int t, const int col)
	{
		if(s <= l && r <= t)
		{
			flag = 1;
			Xor = 0;
			color = col;
			return;
		}
		update();
		if(s <= m) ch[0] -> fill(s, t, col);
		if(t > m) ch[1] -> fill(s, t, col);
	}
	void rev(const int s, const int t)
	{
		if(s <= l && r <= t)
		{
			Xor ^= 1;
			return;
		}
		update();
		if(s <= m) ch[0] -> rev(s, t);
		if(t > m) ch[1] -> rev(s, t);
	}
	void make_tree()
	{
		if(l == r) return;
		(ch[0] = new SegmentTree(l, m)) -> make_tree();
		(ch[1] = new SegmentTree(m + 1, r)) -> make_tree();
	}
	void pre()
	{
		if(flag)
		{
			color ^= Xor;
			if(color) { out[tot][0] = l; out[tot++][1] = r; }
			return;
		}
		update();
		ch[0] -> pre();
		ch[1] -> pre();
	}
} *root;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	char type, flag_l, flag_r;
	int l, r;
	(root = new SegmentTree(0, n)) -> make_tree();
	while(scanf("%c %c%d,%d%c\n", &type, &flag_l, &l, &r, &flag_r) == 5)
	{
		l <<= 1;
		r <<= 1;
		if(flag_l == '(') ++l;
		if(flag_r == ')') --r;
		switch(type)
		{
			case 'U': root -> fill(l, r, 1); break;
			case 'I': if(l) root -> fill(0, l - 1, 0); if(r < n) root -> fill(r + 1, n, 0); break;
			case 'D': root -> fill(l, r, 0); break;
			case 'C': if(l) root -> fill(0, l - 1, 0); if(r < n) root -> fill(r + 1, n, 0); root -> rev(l, r); break;
			case 'S': root -> rev(l, r); break;
		}
	}
	root -> pre();
	if(!tot) printf("empty set\n");
	else
	{
		int i;
		for(i = 0; i < tot - 1; ++i)
			if(out[i][1] + 1 == out[i + 1][0]) out[i + 1][0] = out[i][0];
			else
			{
				if(out[i][0] & 1) putchar('(');
				else putchar('[');
				printf("%d,%d", out[i][0] >> 1, out[i][1] + 1 >> 1);
				if(out[i][1] & 1) putchar(')');
				else putchar(']');
				putchar(' ');
			}
		if(out[i][0] & 1) putchar('(');
		else putchar('[');
		printf("%d,%d", out[i][0] >> 1, out[i][1] + 1 >> 1);
		if(out[i][1] & 1) putchar(')');
		else putchar(']');
		if((out[i][1] + 1 >> 1) != 65535) putchar(' ');//丧心病狂 
		putchar('\n');
	}
#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}
