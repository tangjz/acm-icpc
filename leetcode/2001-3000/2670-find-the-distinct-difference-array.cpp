class Solution {
public:
    vector<int> distinctDifferenceArray(vector<int>& A) {
        int n = A.size();
        vector<int> ret(n);
        unordered_set<int> hs;
        for(int i = 0; i < n; ++i) {
            hs.insert(A[i]);
            ret[i] += hs.size();
        }
        hs.clear();
        for(int i = n - 1; i >= 0; --i) {
            ret[i] -= hs.size();
            hs.insert(A[i]);
        }
        return ret;
    }
};
