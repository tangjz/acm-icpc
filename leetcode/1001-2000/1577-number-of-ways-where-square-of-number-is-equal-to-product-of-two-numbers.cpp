class Solution {
    int solve(vector<int> &lft, vector<int> &rht) {
        typedef long long LL;
        unordered_map<LL, int> Hash;
        for(int x : lft)
            ++Hash[(LL)x * x];
        int n = (int)rht.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                auto it = Hash.find((LL)rht[i] * rht[j]);
                if(it != Hash.end())
                    ans += it -> second;
            }
        return ans;
    }
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        return solve(nums1, nums2) + solve(nums2, nums1);
    }
};
