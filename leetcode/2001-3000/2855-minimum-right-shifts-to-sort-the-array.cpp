class Solution {
public:
    int minimumRightShifts(vector<int>& A) {
        int n = A.size(), x = min_element(A.begin(), A.end()) - A.begin();
        rotate(A.begin(), A.begin() + x, A.end());
        for(int i = 1; i < n; ++i)
            if(A[i - 1] >= A[i])
                return -1;
        return (n - x) % n;
    }
};
