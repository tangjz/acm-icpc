class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int n = (int)nums1.size(), m = (int)nums2.size();
        vector<int> que(nums1.begin(), nums1.end());
        que.insert(que.end(), nums2.begin(), nums2.end());
        inplace_merge(que.begin(), que.begin() + n, que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int tot = (int)que.size();
        unordered_map<int, int> idx;
        for(int i = 0; i < tot; ++i)
            idx.insert({que[i], i});
        vector<pair<int, int> > e(tot, {-1, -1});
        for(int i = 1; i < n; ++i)
            e[idx[nums1[i]]].first = idx[nums1[i - 1]];
        for(int i = 1; i < m; ++i)
            e[idx[nums2[i]]].second = idx[nums2[i - 1]];
        vector<long long> dp(tot, -1LL);
        dp[idx[nums1[0]]] = nums1[0];
        dp[idx[nums2[0]]] = nums2[0];
        for(int i = 0; i < tot; ++i) {
            if(e[i].first != -1 && dp[e[i].first] != -1)
                dp[i] = max(dp[i], dp[e[i].first] + que[i]);
            if(e[i].second != -1 && dp[e[i].second] != -1)
                dp[i] = max(dp[i], dp[e[i].second] + que[i]);
        }
        return max(dp[idx[nums1.back()]], dp[idx[nums2.back()]]) % ((int)1e9 + 7);
    }
};
