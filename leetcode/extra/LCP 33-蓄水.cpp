class Solution {
public:
    int storeWater(vector<int>& bucket, vector<int>& vat) {
        int n = vat.size(), mx = *max_element(vat.begin(), vat.end()), ans = INT_MAX;
        if(!mx)
            ans = 0;
        for(int i = 1; i <= mx; ++i) {
            int tmp = i;
            for(int j = 0; j < n; ++j) {
                if(!vat[j])
                    continue;
                int low = (vat[j] - 1) / i + 1;
                tmp += max(low - bucket[j], 0);
            }
            ans = min(ans, tmp);
        }
        return ans;
    }
};
