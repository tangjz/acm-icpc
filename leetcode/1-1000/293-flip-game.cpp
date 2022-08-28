class Solution {
public:
    vector<string> generatePossibleNextMoves(string A) {
        int n = A.size();
        vector<string> ret;
        for(int i = 0; i + 1 < n; ++i)
            if(A[i] == '+' && A[i + 1] == '+') {
                ret.push_back(A);
                ret.back()[i] = ret.back()[i + 1] = '-';
            }
        return ret;
    }
};
