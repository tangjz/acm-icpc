class Solution {
public:
    int numberOfPairs(vector<int>& nums) {
        static const int maxl = 11, mod = (int)1e9 + 7;
        int ans = 0;
        unordered_map<int, int> ctr;
        for(int x: nums) {
            static char buf[maxl];
            int len = sprintf(buf, "%d", x), y;
            reverse(buf, buf + len);
            sscanf(buf, "%d", &y);
            // printf("%d: %d\n", x, y);
            (ans += ctr[x - y]++) >= mod && (ans -= mod);
        }
        return ans;
    }
};
