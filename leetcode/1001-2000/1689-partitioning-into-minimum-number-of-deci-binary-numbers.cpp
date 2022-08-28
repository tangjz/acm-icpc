class Solution {
public:
    int minPartitions(string n) {
        int ans = 0;
        for(char ch: n)
            ans = max(ans, (int)(ch - '0'));
        return ans;
    }
};
