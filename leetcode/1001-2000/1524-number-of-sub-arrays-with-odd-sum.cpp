class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int mod = (int)1e9 + 7;
        int ans = 0, cnt[2] = {}, sum = 0;
        for(int x : arr) {
            ++cnt[sum];
            sum ^= x & 1;
            (ans += cnt[!sum]) >= mod && (ans -= mod);
        }
        return ans;
    }
};
