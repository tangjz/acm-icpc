class Solution {
public:
    bool canAliceWin(vector<string>& a, vector<string>& b) {
        int n = a.size(), m = b.size();
        int cA = 0, cB = 0, rA = n - 1, rB = m - 1;
        vector<bool> sA(n), sB(m);
        for(int i = n - 1, j = m - 1; i >= 0 || j >= 0; )
            if(j < 0 || (i >= 0 && a[i] > b[j])) {
                for( ; j < rB && b[rB][0] > a[i][0] + 1; cB -= sB[rB--]);
                sA[i] = !cB;
                cA += sA[i--];
            } else {
                for( ; i < rA && a[rA][0] > b[j][0] + 1; cA -= sA[rA--]);
                sB[j] = !cA;
                cB += sB[j--];
            }
        return sA[0];
    }
};
