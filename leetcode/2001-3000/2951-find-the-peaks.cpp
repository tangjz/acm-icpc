class Solution {
public:
    vector<int> findPeaks(vector<int>& A) {
        int n = A.size();
        vector<int> res;
        for(int i = 1; i < n - 1; ++i)
            if(A[i - 1] < A[i] && A[i] > A[i + 1])
                res.push_back(i);
        return res;
    }
};
