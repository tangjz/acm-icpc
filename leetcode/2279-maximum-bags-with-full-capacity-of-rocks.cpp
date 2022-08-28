class Solution {
public:
    int maximumBags(vector<int>& A, vector<int>& B, int adt) {
        int n = A.size();
        vector<int> ctr(n);
        for(int i = 0; i < n; ++i)
            ctr[i] = A[i] - B[i];
        sort(ctr.begin(), ctr.end(), greater<>());
        while(!ctr.empty() && ctr.back() <= adt) {
            adt -= ctr.back();
            ctr.pop_back();
        }
        return n - ctr.size();
    }
};
