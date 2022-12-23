class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        typedef long long LL;
        int n = nums.size();
        LL ans = 0;
        vector<pair<int, int> > low, upp;
        for(int i = 0; i < n; ++i) {
            int v = nums[i];
            for( ; !low.empty() && low.back().first >= v; low.pop_back());
            low.push_back({v, i});
            for( ; !upp.empty() && upp.back().first >= -v; upp.pop_back());
            upp.push_back({-v, i});
            auto it = lower_bound(low.begin(), low.end(), make_pair(minK, 0));
            if(it == low.end() || it -> first != minK)
                continue;
            auto jt = lower_bound(upp.begin(), upp.end(), make_pair(-maxK, 0));
            if(jt == upp.end() || jt -> first != -maxK)
                continue;
            int L = -1, R = min(it -> second, jt -> second);
            if(it != low.begin()) {
                L = max(L, (--it) -> second);
            }
            if(jt != upp.begin()) {
                L = max(L, (--jt) -> second);
            }
            ans += max(R - L, 0);
        }
        return ans;
    }
};
