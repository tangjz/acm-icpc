class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        const int maxc = 5;
        const pair<string, string> cand[maxc] = {
            {"0", "0"},
            {"1", "1"},
            {"6", "9"},
            {"8", "8"},
            {"9", "6"},
        };
        vector<string> f, g;
        if(n & 1) {
            for(int i = 0; i < maxc; ++i)
                if(cand[i].first == cand[i].second)
                    f.push_back(cand[i].first);
        } else {
            f.push_back("");
        }
        while(f.front().size() < n) {
            g.clear();
            for(auto &pre: f)
                for(int i = 0; i < maxc; ++i)
                    g.push_back(cand[i].first + pre + cand[i].second);
            f.swap(g);
        }
        g.clear();
        for(auto &pre: f)
            if(pre[0] != '0' || pre == "0")
                g.push_back(pre);
        return move(g);
    }
};
