class Solution {
public:
    string minimizeResult(string pat) {
        auto pos = pat.find('+');
        string lft = pat.substr(0, pos), rht = pat.substr(pos + 1);
        int ans = stoi(lft) + stoi(rht);
        string out = "(" + pat + ")";
        int n = lft.size(), m = rht.size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int tmp = stoi(lft.substr(i)) + stoi(rht.substr(0, m - j));
                if(i > 0)
                    tmp *= stoi(lft.substr(0, i));
                if(j > 0)
                    tmp *= stoi(rht.substr(m - j));
                if(tmp < ans) {
                    ans = tmp;
                    out = lft.substr(0, i) + "(" + lft.substr(i) + "+" + rht.substr(0, m - j) + ")" + rht.substr(m - j);
                }
            }
        return out;
    }
};
