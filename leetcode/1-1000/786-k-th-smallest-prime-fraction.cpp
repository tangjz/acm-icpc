class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        vector<vector<int> > seq;
        seq.reserve(n * (n - 1) / 2);
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                seq.push_back({arr[i], arr[j]});
        nth_element(seq.begin(), seq.begin() + (k - 1), seq.end(), [&](auto const &lft, auto const &rht) {
            return lft[0] * rht[1] < rht[0] * lft[1];
        });
        return seq[k - 1];
    }
};
