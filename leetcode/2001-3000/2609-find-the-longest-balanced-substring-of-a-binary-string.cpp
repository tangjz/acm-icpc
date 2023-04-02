class Solution {
public:
    int findTheLongestBalancedSubstring(string s) {
        int n = s.size();
        vector<pair<char, int> > seq;
        for(int i = 0; i < n; ) {
            seq.push_back({s[i], 0});
            int &c = seq.back().second;
            for( ; i < n && s[i] == seq.back().first; ++i, ++c);
        }
        int ans = 0, m = seq.size();
        for(int i = 1; i < m; ++i)
            if(seq[i].first == '1')
                ans = max(ans, min(seq[i - 1].second, seq[i].second));
        return ans * 2;
    }
};
