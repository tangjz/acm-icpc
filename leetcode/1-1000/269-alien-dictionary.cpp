class Solution {
public:
    string alienOrder(vector<string>& words) {
        const int maxc = 26;
        int n = words.size();
        vector<int> deg(maxc);
        vector<vector<int> > e(maxc);
        unordered_set<char> sp;
        for(int i = 0; i < n; ++i) {
            for(char ch: words[i])
                sp.insert(ch);
            for(int j = 0; j < i; ++j) {
                int k = 0, upp = min(words[i].size(), words[j].size());
                for( ; k < upp && words[i][k] == words[j][k]; ++k);
                if(k < upp) {
                    int u = words[j][k] - 'a';
                    int v = words[i][k] - 'a';
                    e[u].push_back(v);
                    ++deg[v];
                } else if(words[j].size() > words[i].size()) {
                    return "";
                }
            }
        }
        string que = "";
        for(char ch: sp) {
            int u = ch - 'a';
            if(!deg[u])
                que.push_back(ch);
        }
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i] - 'a';
            for(int v: e[u])
                if(!(--deg[v]))
                    que.push_back('a' + v);
        }
        return que.size() == sp.size() ? que : "";
    }
};
