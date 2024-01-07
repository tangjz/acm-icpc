#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define N 100

struct Node {
	Node() {
		f[0] = f[1] = -1;
	}
	char name[N + 9];
	vector<Node> sub;
	int f[2];
};

int T, n;
char str[N + 9];

void insert(Node &u, char s[], bool flag) {
	char *p = strchr(s, '/');
	if (!p) {
		u.f[flag] = 1;
		u.f[!flag] = 0;
		return;
	}
	*p = '\0';
	for (auto &v: u.sub)
		if (!strcmp(v.name, s)) {
			insert(v, p + 1, flag);
			return;
		}
	u.sub.emplace_back();
	strcpy(u.sub.back().name, s);
	insert(u.sub.back(), p + 1, flag);
}

int dps(Node &u, bool flag) {
	//if (~u.f[flag]) printf("%s, %d: %d\n", u.name, flag, u.f[flag]);
	if (~u.f[flag]) return u.f[flag];
	int s = 0, t = 1;
	for (auto &v: u.sub) {
		s += dps(v, flag);
		t += dps(v, !flag);
	}
	//printf("%s, %d: %d\n", u.name, flag, min(s, t));
	return (u.f[flag] = min(s, t));
}

void destroy(Node &u) {
	for (auto v: u.sub) destroy(v);
	u.sub.clear();
}

int main() {
	scanf("%d", &T);
	while (T--) {
		Node root;
		strcpy(root.name, "/");
		scanf("%d", &n);
		while (n--) {
			scanf("%s", str);
			bool flag = strcmp(str, "stage");
			scanf("%s", str);
			strcat(str, "/");
			insert(root, str + 1, flag);
		}
		printf("%d\n", dps(root, false));
		destroy(root);
	}
	return 0;
}
