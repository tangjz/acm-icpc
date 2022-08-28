class Solution {
public:
    string compressString(string S) {
        int n = (int)S.size();
        string T = "";
        for(int i = 0, j; i < n; i = j) {
            for(j = i; j < n && S[i] == S[j]; ++j);
            T.push_back(S[i]);
            T += to_string(j - i);
        }
        return S.size() > T.size() ? move(T) : move(S);
    }
};
