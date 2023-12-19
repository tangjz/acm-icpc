class Solution {
public:
    int minOperations(vector<int>& A, vector<int>& B) {
        int n = A.size(), ans = INT_MAX;
        for(int i = 0; i < 2; ++i) {
            int tmp = i, uppA = A.back(), uppB = B.back();
            for(int j = 0; j < n; ++j) {
                int xA = A[j], xB = B[j];
                if(xA <= uppA && xB <= uppB)
                    continue;
                if(xB <= uppA && xA <= uppB) {
                    ++tmp;
                    continue;
                }
                tmp = INT_MAX;
                break;
            }
            ans = min(ans, tmp);
            swap(A.back(), B.back());
        }
        return ans < INT_MAX ? ans : -1;
    }
};
