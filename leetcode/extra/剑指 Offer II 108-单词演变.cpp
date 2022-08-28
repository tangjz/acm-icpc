class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> Hash;
        for(auto &it : wordList)
            Hash.insert(make_pair(it, (int)Hash.size()));
        if(!Hash.count(endWord))
            return 0;
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
        vector<int> dist(Hash.size(), 0);
        queue<int> que;
        for(int x : getNext(beginWord))
            if(!dist[x]) {
                dist[x] = 2;
                que.push(x);
            }
        int &ret = dist[Hash[endWord]];
        while(!ret && !que.empty()) {
            int u = que.front();
            que.pop();
            for(int v : getNext(wordList[u]))
                if(!dist[v]) {
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
        }
        return ret;
    }
};
