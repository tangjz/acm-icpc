#include <bits/stdc++.h>
using namespace std;
const int maxd = 7;
int day;
map<string, int> ech[maxd], com;
set<pair<int, string> > Hash;
char buf[1 << 5 | 1];
int main() {
	while(scanf("%s", buf) == 1) {
		assert(buf[0] == '<' && buf[1] == 't');
		if(buf[2] == 'e') {
			for(map<string, int>::iterator it = ech[day].begin(); it != ech[day].end(); ++it) {
				int ctr = com[it -> first];
				if(ctr)
					Hash.erase(make_pair(-ctr, it -> first));
				ctr = com[it -> first] -= it -> second;
				if(ctr)
					Hash.insert(make_pair(-ctr, it -> first));
			}
			map<string, int>().swap(ech[day]);
			while(scanf("%s", buf) == 1 && buf[0] != '<')
				if(strlen(buf) >= 4)
					ech[day][buf] += 1;
			for(map<string, int>::iterator it = ech[day].begin(); it != ech[day].end(); ++it) {
				int ctr = com[it -> first];
				if(ctr)
					Hash.erase(make_pair(-ctr, it -> first));
				ctr = com[it -> first] += it -> second;
				if(ctr)
					Hash.insert(make_pair(-ctr, it -> first));
			}
			day = (day + 1) % maxd;
		} else {
			assert(buf[2] == 'o');
			scanf("%s", buf);
			int num;
			sscanf(buf, "%d", &num);
			scanf("%s", buf);
			printf("<top %d>\n", num);
			set<pair<int, string> >::iterator it = Hash.begin();
			while(num > 0 && it != Hash.end()) {
				int ctr = it -> first;
				while(it != Hash.end() && ctr == it -> first) {
					printf("%s %d\n", (it -> second).c_str(), -(it -> first));
					--num;
					++it;
				}
			}
			printf("</top>\n");
		}
	}
	return 0;
}
