class Solution {
public:
    vector<int> numberGame(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end());
        for(int i = 0; i + 1 < n; i += 2)
            swap(A[i], A[i + 1]);
        return A;
    }
};
