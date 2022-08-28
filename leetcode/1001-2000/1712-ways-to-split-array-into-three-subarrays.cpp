class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        int n = nums.size();
        vector<int> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        long long ans = 0;
        for(int i = 2, pL = 1, pR = 1; i < n; ++i) {
            // [0, j): psum[j] - psum[0]
            // [j, i): psum[i] - psum[j]
            // [i, n): psum[n] - psum[i]
            
            // 0 < j < i
            // psum[j] <= psum[i] / 2
            // psum[j] >= 2 psum[i] - psum[n]
            for( ; pL < i && psum[pL] < psum[i] + psum[i] - psum[n]; ++pL);
            for( ; pR < i && psum[pR] <= psum[i] / 2; ++pR);
            ans += max(pR - pL, 0);
        }
        return ans % ((int)1e9 + 7);
    }
};
