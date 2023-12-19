class Solution {
public:
    vector<int> lastVisitedIntegers(vector<string>& A) {
        int n = A.size();
        vector<int> ret, seq;
        for(int i = 0; i < n; ) {
            if(A[i] != "prev") {
                seq.push_back(stoi(A[i++]));
                continue;
            }
            for(int j = seq.size() - 1; i < n && A[i] == "prev"; ++i, --j)
                ret.push_back(j < 0 ? -1 : seq[j]);
        }
        return ret;
    }
};
