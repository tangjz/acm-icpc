class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        const int maxd = 26;
        int m = beginWord.size();
        vector<int> pw(m + 1);
        pw[0] = 1;
        for(int i = 0; i < m; ++i)
            pw[i + 1] = pw[i] * maxd;
        auto getHash = [&](string const &u) {
            assert(u.size() == m);
            int ret = 0;
            for(int i = m - 1; i >= 0; --i)
                ret = ret * 26 + (u[i] - 'a');
            return ret;
        };
        unordered_map<int, int> Hash;
        vector<pair<int, string> > seq;
        int beg = getHash(beginWord), end = getHash(endWord);
        if(Hash.insert(make_pair(beg, (int)Hash.size())).second)
            seq.push_back({beg, beginWord});
        for(auto &it : wordList) {
            int hh = getHash(it);
            if(Hash.insert(make_pair(hh, (int)Hash.size())).second)
                seq.push_back({hh, it});
        }
        if(!Hash.count(end))
            return {};
        auto getNext = [&](int cur) {
            vector<int> vec;
            for(int i = 0, tmp = cur; i < m; ++i, tmp /= maxd) {
                int tp = tmp % maxd;
                for(int j = 0; j < maxd; ++j) {
                    if(j == tp)
                        continue;
                    int nxt = cur + (j - tp) * pw[i];
                    auto it = Hash.find(nxt);
                    if(it != Hash.end())
                        vec.push_back(it -> second);
                }
            }
            return vec;
        };
        vector<int> dist(Hash.size(), 0);
        queue<int> que;
        assert(Hash[beg] == 0);
        dist[0] = 1;
        que.push(0);
        int &ret = dist[Hash[end]];
        while(!ret && !que.empty()) {
            int u = que.front();
            que.pop();
            for(int v : getNext(seq[u].first))
                if(!dist[v]) {
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
        }
        if(!ret)
            return {};
        vector<int> idx(ret);
        vector<string> path(ret);
        vector<vector<string> > out;
        function<void(int)> dfs = [&](int dep) {
            if(!dep) {
                out.push_back(path);
                return;
            }
            int u = idx[dep];
            for(int v: getNext(seq[u].first))
                if(dist[v] == dist[u] - 1) {
                    idx[dep - 1] = v;
                    path[dep - 1] = seq[v].second;
                    dfs(dep - 1);
                }
        };
        idx[ret - 1] = Hash[end];
        path[ret - 1] = endWord;
        dfs(ret - 1);
        return out;
    }
};
