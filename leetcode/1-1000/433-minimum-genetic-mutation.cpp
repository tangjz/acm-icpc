class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_map<string, int> Hash;
        for(auto &it : bank)
            Hash.insert(make_pair(it, (int)Hash.size()));
        if(!Hash.count(end))
            return -1;
        auto getNext = [&](string cur) {
            vector<int> vec;
            int len = (int)cur.length();
            for(int i = 0; i < len; ++i) {
                char tp = cur[i];
                for(char ch: "ACGT") {
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
        vector<int> dist(Hash.size(), -1);
        queue<int> que;
        if(Hash.count(start)) {
            int x = Hash[start];
            dist[x] = 0;
            que.push(x);
        } else {
            for(int x : getNext(start))
                if(dist[x] == -1) {
                    dist[x] = 1;
                    que.push(x);
                }
        }
        int &ret = dist[Hash[end]];
        while(ret == -1 && !que.empty()) {
            int u = que.front();
            que.pop();
            for(int v : getNext(bank[u]))
                if(dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
        }
        return ret;
    }
};
