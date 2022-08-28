class Solution {
    struct Subset {
        vector<int> vals;
        void parse(vector<int> &nums) {
            int n = (int)nums.size();
            int m = 1 << n;
            vals.resize(m);
            vals[0] = 0;
            for(int i = 1, j; i < m; ++i) {
                if(i & 1) {
                    j = 0;
                } else {
                    for(++j; !((i >> j) & 1); ++j);
                }
                vals[i] = vals[i ^ (1 << j)] + nums[j];
            }
            sort(vals.begin(), vals.end());
        }
        pair<int, int> findCloset(int x) {
            auto it = lower_bound(vals.begin(), vals.end(), x);
            return {it == vals.begin() ? INT_MIN : *(it - 1), it == vals.end() ? INT_MIN : *it};
        }
    };
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        vector<int> lft, rht;
        for(int x : nums)
            if(lft.size() < rht.size()) {
                lft.push_back(x);
            } else {
                rht.push_back(x);
            }
        Subset A, B;
        A.parse(lft);
        B.parse(rht);
        int ans = abs(goal);
        for(int x : A.vals) {
            pair<int, int> tp = B.findCloset(goal - x);
            for(int y : {tp.first, tp.second})
                if(y != INT_MIN)
                    ans = min(ans, abs(x + y - goal));
        }
        return ans;
    }
};
