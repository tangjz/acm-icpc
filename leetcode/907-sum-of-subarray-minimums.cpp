class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long ans = 0;
        vector<int> pL(n), pR(n);
        for(int i = 0; i < n; ++i)
            for(pL[i] = i - 1; pL[i] >= 0 && arr[i] < arr[pL[i]]; pL[i] = pL[pL[i]]);
        for(int i = n - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < n && arr[i] <= arr[pR[i]]; pR[i] = pR[pR[i]]);
            ans += 1LL * arr[i] * (i - pL[i]) * (pR[i] - i);
        }
        return ans % ((int)1e9 + 7);
    }
};
