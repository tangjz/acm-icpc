class Solution {
    vector<string_view> split(string_view s, char sep = '.') {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0; i < n; ++i) {
            int j = i;
            for( ; i < n && s[i] != sep; ++i);
            ret.push_back(s.substr(j, i - j));
        }
        if(!s.empty() && s.back() == sep)
            ret.push_back(s.substr(s.size()));
        return move(ret);
    }
public:
    bool hasCycle(string graph) {
        map<int, pair<int, vector<int> > > info;
        for(auto &item: split(graph, ',')) {
            auto pos = item.find('>');
            int u = stoi((string)item.substr(0, pos - 1));
            int v = stoi((string)item.substr(pos + 1));
            info.insert({u, {}});
            info.insert({v, {}});
            info[u].second.push_back(v);
            ++info[v].first;
        }
        queue<int> que;
        for(auto &it: info)
            if(!it.second.first)
                que.push(it.first);
        int rem = info.size();
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: info[u].second)
                if(!(--info[v].first))
                    que.push(v);
            --rem;
        }
        return rem;
    }
};
