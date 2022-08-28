class Solution {
public:
    int expectNumber(vector<int>& scores) {
        sort(scores.begin(), scores.end());
        return unique(scores.begin(), scores.end()) - scores.begin();
    }
};
