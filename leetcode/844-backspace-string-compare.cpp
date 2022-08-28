class Solution {
public:
    bool backspaceCompare(string S, string T) {
        for(int i = (int)S.length() - 1, j = (int)T.length() - 1; ; --i, --j) {
            for(int ctr = 0; i >= 0 && (S[i] == '#' || ctr > 0); --i)
                ctr += S[i] == '#' ? 1 : -1;
            for(int ctr = 0; j >= 0 && (T[j] == '#' || ctr > 0); --j)
                ctr += T[j] == '#' ? 1 : -1;
            bool ok0 = i < 0, ok1 = j < 0;
            if(ok0 != ok1)
                return 0;
            if(ok0)
                return 1;
            if(S[i] != T[j])
                return 0;
        }
    }
};
