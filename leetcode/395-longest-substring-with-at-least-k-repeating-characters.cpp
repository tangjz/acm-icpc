class Solution {
public:
    int longestSubstring(string s, int k) {
        const int maxc = 26;
        int n = s.size(), ans = 0;
        vector<pair<int, int> > seq;
        vector<vector<int> > pos(maxc);
        for(int i = n - 1; i >= 0; --i) {
            int o = s[i] - 'a';
            pos[o].push_back(i);
            int sz = pos[o].size(), nxt = sz < k ? n : pos[o][sz - k];
            int las = 0;
            for(sz = seq.size(); las < sz && s[seq[las].first] != s[i]; ++las);
            if(las == sz) {
                seq.push_back({});
                ++sz;
            }
            seq[las] = {i, nxt};
            rotate(seq.begin(), seq.begin() + las, seq.begin() + las + 1);
            int low = i, upp;
            for(int j = 0; j < sz; ++j) {
                low = max(low, seq[j].second);
                upp = j + 1 < sz ? seq[j + 1].first : n;
                if(low < upp)
                    ans = max(ans, upp - i);
            }
        }
        return ans;
    }
};
