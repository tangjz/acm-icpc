class Solution {
public:
    int longestESR(vector<int>& sales) {
        int ans = 0, pos = 0, sum = 0;
        vector<pair<int, int> > stk;
        stk.push_back({0, -1});
        for(int x: sales) {
            x = x > 8 ? -1 : 1;
            sum += x;
            auto it = lower_bound(stk.begin(), stk.end(), make_pair(sum + 1, -1));
            if(it != stk.end())
                ans = max(ans, pos - it -> second);
            if(stk.empty() || stk.back().first < sum)
                stk.push_back({sum, pos});
            ++pos;
        }
        return ans;
    }
};
