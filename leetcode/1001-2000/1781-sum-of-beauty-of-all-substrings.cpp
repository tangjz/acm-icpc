class Solution {
public:
    int beautySum(string s) {
        const int maxd = 26;
        int n = (int)s.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            vector<int> ctr(maxd, 0);
            for(int j = i; j < n; ++j) {
                int cur = s[j] - 'a', low = cur, upp = cur;
                ++ctr[cur];
                for(int k = 0; k < maxd; ++k)
                    if(ctr[k] > 0) {
                        if(ctr[k] < ctr[low]) {
                            low = k;
                        } else if(ctr[k] > ctr[upp]) {
                            upp = k;
                        }
                    }
                ans += ctr[upp] - ctr[low];
            }
        }
        return ans;
    }
};
