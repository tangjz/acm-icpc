class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size(), m = 0;
        vector<int> dep;
        dep.reserve(n);
        for(char ch: seq)
            if(ch == '(') {
                dep.push_back((m++) & 1);
            } else {
                dep.push_back((--m) & 1);
            }
        return dep;
    }
};
