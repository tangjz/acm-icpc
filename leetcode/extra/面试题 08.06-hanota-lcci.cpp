class Solution {
    void calc(int sz, vector<int> &A, vector<int> &B, vector<int> &C) {
        if(sz > 0) {
            calc(sz - 1, A, C, B);
            C.push_back(A.back());
            A.pop_back();
            calc(sz - 1, B, A, C);
        }
    }
public:
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
        calc(A.size(), A, B, C);
    }
};
