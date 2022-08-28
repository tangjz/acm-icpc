class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        const int maxd = 4, pw[] = {1, 10, 100, 1000, 10000};
        unordered_set<int> ban;
        for(auto &it : deadends)
            ban.insert(stoi(it));
        auto getNext = [&](int cur) {
            vector<int> vec;
            for(int i = 0, tmp = cur; i < 4; ++i, tmp /= 10) {
                int dig = tmp % 10;
                for(int dx = -1; dx <= 1; dx += 2) {
                    int nxt = cur + ((dig + 10 + dx) % 10 - dig) * pw[i];
                    if(!ban.count(nxt))
                        vec.push_back(nxt);
                }
            }
            return vec;
        };
        vector<int> dist(pw[maxd], -1);
        queue<int> que;
        if(!ban.count(0)) {
            dist[0] = 0;
            que.push(0);
        }
        int &ret = dist[stoi(target)];
        while(ret == -1 && !que.empty()) {
            int u = que.front();
            que.pop();
            for(int v : getNext(u))
                if(dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
        }
        return ret;
    }
};
