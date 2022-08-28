class Solution {
public:
    bool canConvert(string str1, string str2) {
        const int maxd = 26;
        int n = str1.size();
        unordered_map<int, int> nxt;
        unordered_set<int> vis;
        for(int i = 0; i < n; ++i) {
            int u = str1[i] - 'a', v = str2[i] - 'a';
            auto it = nxt.find(u);
            if(it != nxt.end()) {
                if(it -> second != v)
                    return 0;
            } else {
                nxt.insert({u, v});
            }
            vis.insert(v);
        }
        return vis.size() < maxd || str1 == str2;
    }
};
