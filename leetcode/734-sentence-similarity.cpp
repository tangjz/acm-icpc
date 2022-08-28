class Solution {
public:
    bool areSentencesSimilar(vector<string>& A, vector<string>& B, vector<vector<string>>& C) {
        if(A.size() != B.size())
            return 0;
        int n = A.size();
        set<pair<string, string> > eq;
        for(int i = 0; i < n; ++i) {
            if(A[i] == B[i])
                continue;
            if(A[i] > B[i])
                A[i].swap(B[i]);
            eq.insert({move(A[i]), move(B[i])});
        }
        for(auto &it: C) {
            if(it[0] > it[1])
                it[0].swap(it[1]);
            eq.erase({it[0], it[1]});
        }
        return eq.empty();
    }
};
