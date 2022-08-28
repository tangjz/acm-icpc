class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        vector<int> B[2];
        for(int x : A)
            B[x & 1].push_back(x);
        B[0].insert(B[0].end(), B[1].begin(), B[1].end());
        return B[0];
    }
};
