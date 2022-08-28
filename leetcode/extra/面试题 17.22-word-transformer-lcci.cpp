class Solution {
public:
    vector<string> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> Hash;
        vector<string> seq;
        for(auto &it : wordList)
            if(Hash.insert(make_pair(it, (int)Hash.size())).second)
                seq.push_back(it);
        if(!Hash.count(endWord))
            return {};
        auto getNext = [&](string cur) {
            vector<int> vec;
            int len = (int)cur.length();
            for(int i = 0; i < len; ++i) {
                char tp = cur[i];
                for(char ch = 'a'; ch <= 'z'; ++ch) {
                    if(ch == tp)
                        continue;
                    cur[i] = ch;
                    auto it = Hash.find(cur);
                    if(it != Hash.end())
                        vec.push_back(it -> second);
                    cur[i] = tp;
                }
            }
            return vec;
        };
        vector<int> dist(Hash.size(), 0), pre(Hash.size(), -1);
        queue<int> que;
        for(int x : getNext(beginWord))
            if(!dist[x]) {
                dist[x] = 2;
                que.push(x);
            }
        int dst = Hash[endWord];
        int &ret = dist[dst];
        while(!ret && !que.empty()) {
            int u = que.front();
            que.pop();
            for(int v : getNext(wordList[u]))
                if(!dist[v]) {
                    pre[v] = u;
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
        }
        if(!ret)
            return {};
        vector<string> path;
        while(dst != -1 && dist[dst] >= 2) {
            path.push_back(seq[dst]);
            dst = pre[dst];
        }
        path.push_back(beginWord);
        reverse(path.begin(), path.end());
        return path;
    }
};
