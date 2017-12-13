#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001, INF = 0x3f3f3f3f;
int t, n, m, que[maxn][3], pos[maxn], tot, ord[maxn];
struct Node {
	int fa, lch, rch;
	int p[2], pMin[2], pMax[2];
	int v, vMin, vPos, vTag;
	void init(int _fa, int _p[2]) {
		fa = _fa;
		lch = rch = 0;
		p[0] = pMin[0] = pMax[0] = _p[0];
		p[1] = pMin[1] = pMax[1] = _p[1];
		v = vMin = INF;
		vTag = 0;
	}
	void upd(Node const &ch) {
		pMin[0] > ch.pMin[0] && (pMin[0] = ch.pMin[0]);
		pMin[1] > ch.pMin[1] && (pMin[1] = ch.pMin[1]);
		pMax[0] < ch.pMax[0] && (pMax[0] = ch.pMax[0]);
		pMax[1] < ch.pMax[1] && (pMax[1] = ch.pMax[1]);
	}
	void adt(int tag) {
		v += tag;
		vMin += tag;
		vTag += tag;
	}
} tree[maxn];
int kd_build(int L, int R, int o, int fa) {
	int M = (L + R) >> 1;
	nth_element(ord + L, ord + M, ord + R + 1, [&](int const &u, int const &v) {
		return que[u][o] < que[v][o];
	});
	pos[ord[M]] = M;
	tree[M].init(fa, que[ord[M]]);
	if(L < M) {
		tree[M].lch = kd_build(L, M - 1, o ^ 1, M);
		tree[M].upd(tree[tree[M].lch]);
	}
	if(M < R) {
		tree[M].rch = kd_build(M + 1, R, o ^ 1, M);
		tree[M].upd(tree[tree[M].rch]);
	}
	return M;
}
void kd_up(int rt) {
	int lch = tree[rt].lch, rch = tree[rt].rch;
	tree[rt].vMin = tree[rt].v;
	tree[rt].vPos = rt;
	if(tree[lch].vMin < tree[rt].vMin) {
		tree[rt].vMin = tree[lch].vMin;
		tree[rt].vPos = tree[lch].vPos;
	}
	if(tree[rch].vMin < tree[rt].vMin) {
		tree[rt].vMin = tree[rch].vMin;
		tree[rt].vPos = tree[rch].vPos;
	}
}
void kd_down(int rt) {
	if(tree[rt].vTag) {
		if(tree[rt].lch)
			tree[tree[rt].lch].adt(tree[rt].vTag);
		if(tree[rt].rch)
			tree[tree[rt].rch].adt(tree[rt].vTag);
		tree[rt].vTag = 0;
	}
}
void kd_access(int rt) {
	if(tree[rt].fa)
		kd_access(tree[rt].fa);
	kd_down(rt);
}
void kd_set(int rt, int v) {
	kd_access(rt);
	tree[rt].v = v;
	for( ; rt; rt = tree[rt].fa)
		kd_up(rt);
}
void kd_upd(int rt, int pos, int v) {
	if(tree[rt].pMax[0] <= pos && tree[rt].pMin[1] >= pos) {
		tree[rt].adt(v);
		return;
	}
	if(tree[rt].pMin[0] > pos || tree[rt].pMax[1] < pos)
		return;
	if(tree[rt].p[0] <= pos && tree[rt].p[1] >= pos)
		tree[rt].v += v;
	kd_down(rt);
	if(tree[rt].lch)
		kd_upd(tree[rt].lch, pos, v);
	if(tree[rt].rch)
		kd_upd(tree[rt].rch, pos, v);
	kd_up(rt);
}
int cnt, out[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		tot = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			char op[3];
			scanf("%s", op);
			if(op[0] == 'C') {
				scanf("%d%d%d", que[i] + 0, que[i] + 1, que[i] + 2);
				ord[++tot] = i;
			} else { // op[0] == 'G'
				scanf("%d", que[i] + 0);
				que[i][2] = 0;
			}
		}
		printf("Case #%d:\n", Case);
		int rt = kd_build(1, tot, 0, 0);
		tree[0].v = tree[0].vMin = INF;
		tree[0].vTag = 0;
		for(int i = 1, msk = 0; i <= n; ++i)
			if(que[i][2]) {
				kd_set(pos[i], que[i][2]);
			} else {
				kd_upd(rt, que[i][0] ^ msk, -1);
				for(cnt = 0; !tree[rt].vMin; kd_set(tree[rt].vPos, INF))
					out[++cnt] = ord[tree[rt].vPos];
				if(cnt) {
					sort(out + 1, out + cnt + 1);
					printf("%d", i);
					for(int j = 1; j <= cnt; msk ^= out[j++])
						printf(" %d", out[j]);
					puts("");
				}
			}
	}
	return 0;
}
