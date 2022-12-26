/*
 * 按分数和插入时间为关键字做SBT
 * 指针的增减浪费时间
 */
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
const int maxn = 250001;
int n, total = 0, num_tmp;
map<long long, int> number;
char name[maxn][11] = {};
struct rec
{
	int val, time;
	rec(void) { val = time = 0; }
	rec(const int v, const int t) : val(v), time(t) {}
	bool operator == (const rec &x) const { return val == x.val && time == x.time; }
	bool operator < (const rec &x) const { if(val == x.val) return time > x.time; return val < x.val; }
} data[maxn], data_tmp;
class Treap
{
private:
	struct Node
	{
		int ch[2], rnd, num, sum; rec val;
		bool operator < (const Node &rhs) const { return rnd < rhs.rnd; }
		int cmp(void) const { if(val == data_tmp) return -1; return val < data_tmp; }
	} tree[maxn];
	int root, tree_size;
	void init(void) { root = tree_size = tree[0].sum = 0; }
	void maintain(const int now) { tree[now].sum = tree[tree[now].ch[0]].sum + tree[tree[now].ch[1]].sum + 1; }
	void rotate(int &now, const int d)
	{
		int tmp = tree[now].ch[d ^ 1]; tree[now].ch[d ^ 1] = tree[tmp].ch[d]; tree[tmp].ch[d] = now;
		maintain(now); maintain(tmp); now = tmp;
	}
	void insert(int &now)
	{
		if(!now)
		{
			now = ++tree_size;
			tree[now].ch[0] = tree[now].ch[1] = 0;
			tree[now].rnd = rand();
			tree[now].num = num_tmp;
			tree[now].sum = 1;
			tree[now].val = data_tmp;
		}
		else
		{
			int d = tree[now].cmp();
			insert(tree[now].ch[d]);
			if(tree[now] < tree[tree[now].ch[d]]) rotate(now, d ^ 1);
		}
		maintain(now);
	}
	void remove(int &now)
	{
		int d = tree[now].cmp();
		if(d == -1)
		{
			if(tree[now].ch[0] && tree[now].ch[1])
			{
				int d2 = tree[tree[now].ch[1]] < tree[tree[now].ch[0]];
				rotate(now, d2);
				remove(tree[now].ch[d2]);
			}
			else if(tree[now].ch[0]) now = tree[now].ch[0];
			else if(tree[now].ch[1]) now = tree[now].ch[1];
			else now = 0;
		}
		else remove(tree[now].ch[d]);
		if(now) maintain(now);
	}
public:
	void ins(void) { insert(root); }
	void del(void) { remove(root); }
	void kth(int k)
	{
		int now = root;
		while(now)
		{
			int sum = tree[tree[now].ch[1]].sum;
			if(k == sum + 1) break;
			else if(k <= sum) now = tree[now].ch[1];
			else { k -= sum + 1; now = tree[now].ch[0]; }
		}
		printf("%s", name[tree[now].num]);
	}
	void rank(void)
	{
		int now = root, sum = 0;
		while(now)
		{
			int d = tree[now].cmp();
			if(d == 1) now = tree[now].ch[1];
			else
			{
				sum += tree[tree[now].ch[1]].sum + 1;
				if(d == -1) break;
				now = tree[now].ch[0];
			}
		}
		printf("%d\n", sum);
	}
} T;

char flag, ch[11];
long long hash(void) { long long ans = 0; for(int i = 0; ch[i] != '\0'; ++i) ans = ans * 26 + ch[i] - 'A' + 1; return ans; }

int main()
{
	int now, i, score;
	long long hash_key;
	scanf("%d", &n);
	for(now = 1; now <= n; ++now)
	{
		flag = getchar(); while(flag != '+' && flag != '?') flag = getchar();
		scanf("%s", ch);
		if(flag == '+')
		{
			scanf("%d", &score);
			num_tmp = number[hash_key = hash()];
			if(!num_tmp)
			{
				++total;
				for(i = 0; ch[i] != '\0'; ++i) name[total][i] = ch[i];
				num_tmp = number[hash_key] = total;
			}
			else
			{
				data_tmp = data[num_tmp];
				T.del();
			}
			data_tmp = data[num_tmp] = rec(score, now);
			T.ins();
		}
		else
		{
			if(ch[0] >= '0' && ch[0] <= '9')
			{
				sscanf(ch, "%d", &num_tmp);
				T.kth(num_tmp);
				for(i = 1; i < 10 && i + num_tmp <= total; ++i) { putchar(' '); T.kth(num_tmp + i); }
				putchar('\n');
			}
			else
			{
				num_tmp = number[hash()];
				data_tmp = data[num_tmp];
				T.rank();
			}
		}
	}
	return 0;
}
