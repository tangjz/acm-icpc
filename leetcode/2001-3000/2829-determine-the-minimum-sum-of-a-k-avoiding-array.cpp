class Solution {
public:
    int minimumSum(int n, int k) {
        vector<int> seq;
        for(int i = 1, j = k - 1; i <= j; ++i, --j)
            seq.push_back(i);
        for(int i = k; seq.size() < n; ++i)
            seq.push_back(i);
        seq.resize(n);
        return accumulate(seq.begin(), seq.end(), 0);
    }
};
