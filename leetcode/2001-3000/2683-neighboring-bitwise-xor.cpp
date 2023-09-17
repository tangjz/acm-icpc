class Solution {
public:
    bool doesValidArrayExist(vector<int>& A) {
        int ans = 0;
        for(int x: A)
            ans ^= x;
        return !ans;
    }
};
