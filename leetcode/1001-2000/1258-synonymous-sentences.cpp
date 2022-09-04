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
    vector<string> generateSentences(vector<vector<string>>& synonyms, string text) {
        unordered_map<string, int> idx;
        vector<string> seq;
        vector<int> dsu;
        vector<vector<int> > sp;
        auto getID = [&](string const &s) {
            auto ret = idx.insert({s, idx.size()});
            if(ret.second) {
                seq.push_back(s);
                dsu.push_back(-1);
                sp.push_back({(int)sp.size()});
            }
            return ret.first -> second;
        };
        function<int(int)> dsuFind = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
        };
        auto dsuMerge = [&](int u, int v) -> bool {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return 0;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
            sp[v].insert(sp[v].end(), sp[u].begin(), sp[u].end());
            sp[u].clear();
            return 1;
        };
        for(auto &it: synonyms)
            dsuMerge(getID(it[0]), getID(it[1]));
        vector<string> ret = {""}, tmp;
        for(auto &word: split(text, ' ')) {
            tmp.clear();
            int u = dsuFind(getID((string)word));
            tmp.reserve(ret.size() * sp[u].size());
            for(auto &pre: ret)
                for(int id: sp[u])
                    tmp.push_back(pre + seq[id] + " ");
            ret.swap(tmp);
        }
        for(auto &it: ret)
            it.pop_back();
        sort(ret.begin(), ret.end());
        return ret;
    }
};
