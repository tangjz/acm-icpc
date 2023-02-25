class Solution {
public:
    bool isItPossible(string A, string B) {
        const int maxd = 26;
        int vA = 0, vB = 0;
        vector<int> cA(maxd), cB(maxd);
        for(char ch: A) {
            int o = ch - 'a';
            vA += !(cA[o]++);
        }
        for(char ch: B) {
            int o = ch - 'a';
            vB += !(cB[o]++);
        }
        for(int i = 0; i < maxd; ++i) if(cA[i])
            for(int j = 0; j < maxd; ++j) if(cB[j]) {
                vA -= !(--cA[i]);
                vA += !(cA[j]++);
                vB -= !(--cB[j]);
                vB += !(cB[i]++);
                if(vA == vB)
                    return 1;
                vA -= !(--cA[j]);
                vA += !(cA[i]++);
                vB -= !(--cB[i]);
                vB += !(cB[j]++);
            }
        return 0;
    }
};
