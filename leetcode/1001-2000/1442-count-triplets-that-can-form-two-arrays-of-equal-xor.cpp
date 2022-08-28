class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n = (int)arr.size();
        vector<int> sum;
        sum.push_back(0);
        for(int x : arr)
            sum.push_back(sum.back() ^ x);
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                for(int k = j + 1; k <= n; ++k)
                    ans += (sum[i] ^ sum[j]) == (sum[j] ^ sum[k]);
        return ans;
    }
};
