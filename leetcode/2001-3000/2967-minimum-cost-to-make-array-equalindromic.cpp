class Solution {
public:
    long long minimumCost(vector<int>& nums) {
        typedef long long LL;
        static vector<int> cand;
        if(cand.empty()) {
            static const int maxv = (int)1e9;
            for(int i = 1; ; ++i) {
                bool upd = 0;
                string s = to_string(i), t = s;
                t.pop_back();
                reverse(t.begin(), t.end());
                LL v = stol(s + t);
                if(v < maxv) {
                    upd = 1;
                    cand.push_back(v);
                }
                t = s;
                reverse(t.begin(), t.end());
                v = stol(s + t);
                if(v < maxv) {
                    upd = 1;
                    cand.push_back(v);
                }
                if(!upd)
                    break;
            }
            sort(cand.begin(), cand.end());
            // printf("tot: %d, fir: %d, las: %d\n", (int)cand.size(), cand.front(), cand.back());
        }
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int L = nums[(n - 1) / 2], R = nums[n / 2];
        auto it = lower_bound(cand.begin(), cand.end(), L);
        auto calc = [&](vector<int> &A, int y) {
            LL ret = 0;
            for(int x: A)
                ret += abs(x - y);
            return ret;
        };
        if(it != cand.end() && *it <= R)
            return calc(nums, *it);
        LL ret = LLONG_MAX;
        if(it != cand.end())
            ret = min(ret, calc(nums, *it));
        if(it != cand.begin())
            ret = min(ret, calc(nums, *(--it)));
        return ret;
    }
};
