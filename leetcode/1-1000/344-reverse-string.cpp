class Solution {
public:
    void reverseString(vector<char>& s) {
        int n = (int)s.size();
        for(int i = 0, j = n - 1; i < j; ++i, --j)
            swap(s[i], s[j]);
    }
};
