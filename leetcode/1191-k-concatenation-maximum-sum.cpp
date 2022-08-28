class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = arr.size();
        LL pre = 0, suf = 0, mid = 0, all = 0, tmp = 0;
        for(int x: arr) {
            all += x;
            pre = max(pre, all);
            tmp = max(tmp + x, 0LL);
            mid = max(mid, tmp);
        }
        if(k == 1)
            return mid % mod;
        reverse(arr.begin(), arr.end());
        tmp = 0;
        for(int x: arr) {
            tmp += x;
            suf = max(suf, tmp);
        }
        return max(mid, pre + suf + max((k - 2) * all, 0LL)) % mod;
    }
};
