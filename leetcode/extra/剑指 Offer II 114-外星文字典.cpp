class Solution {
public:
    string alienOrder(vector<string>& words) {
        int n = words.size();
        unordered_map<int, vector<int> > e;
        for(int i = 0; i < n; ++i) {
            for(char ch: words[i])
                e.insert({ch - 'a', {}});
            for(int j = i + 1; j < n; ++j) {
                int upp = min(words[i].size(), words[j].size()), pos = 0;
                for( ; pos < upp && words[i][pos] == words[j][pos]; ++pos);
                if(pos == words[j].size()) {
                    if(pos != words[i].size())
                        return "";
                    continue;
                }
                if(pos < words[i].size())
                    e[words[j][pos] - 'a'].push_back(words[i][pos] - 'a');
            }
        }
        string ret = "";
        while(!e.empty()) {
            bool upd = 0;
            for(auto &it: e) {
                bool ban = 0;
                int u = it.first;
                for(int v: it.second)
                    if(e.count(v)) {
                        ban = 1;
                        break;
                    }
                if(!ban) {
                    upd = 1;
                    ret.push_back('a' + u);
                    e.erase(u);
                    break;
                }
            }
            if(!upd)
                return "";
        }
        return ret;
    }
};
