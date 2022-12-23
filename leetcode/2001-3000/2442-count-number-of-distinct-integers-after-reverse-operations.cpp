class Solution {
public:
    int countDistinctIntegers(vector<int>& nums) {
        unordered_set<int> vis;
        for(int x: nums)
            vis.insert(x);
        nums = vector<int>(vis.begin(), vis.end());
        for(int x: nums) {
            static char buf[7];
            int len = sprintf(buf, "%d", x), y;
            reverse(buf, buf + len);
            sscanf(buf, "%d", &y);
            vis.insert(y);
        }
        return vis.size();
    }
};
