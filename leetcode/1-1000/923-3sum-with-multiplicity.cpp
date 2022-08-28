class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        typedef long long LL;
        int mx = *max_element(arr.begin(), arr.end());
        vector<int> ctr(mx + 1);
        for(int x: arr)
            ++ctr[x];
        LL ans = 0;
        for(int i = 0; i <= mx && i * 3 <= target; ++i) if(ctr[i])
            for(int j = i; j <= mx && i + j * 2 <= target; ++j) if(ctr[j]) {
                int k = target - i - j;
                if(k > mx || !ctr[k])
                    continue;
                LL ways = 1;
                ways *= ctr[i]--;
                ways *= ctr[j]--;
                ways *= ctr[k]--;
                if(i == j) {
                    ways >>= 1;
                    if(j == k)
                        ways /= 3;
                } else if(j == k) {
                    ways >>= 1;
                }
                ++ctr[i];
                ++ctr[j];
                ++ctr[k];
                ans += ways;
            }
        return ans % ((int)1e9 + 7);
    }
};
