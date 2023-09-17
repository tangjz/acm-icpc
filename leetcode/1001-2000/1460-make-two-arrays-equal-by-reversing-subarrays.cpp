class Solution {
public:
    bool canBeEqual(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a == b;
    }
};
