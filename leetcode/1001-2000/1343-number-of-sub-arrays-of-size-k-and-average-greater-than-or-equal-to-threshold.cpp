class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = (int)arr.size(), las = 0;
        vector<int> psum;
        psum.push_back(las);
        for(int x : arr)
            psum.push_back(las += x);
        int ans = 0;
        for(int i = k; i <= n; ++i)
            ans += psum[i] - psum[i - k] >= k * threshold;
        return ans;
    }
};
