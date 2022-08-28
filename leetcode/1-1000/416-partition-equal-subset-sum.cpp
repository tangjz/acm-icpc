class Solution {
public:
    bool canPartition(vector<int>& nums) {
        const int maxs = 10001;
        int sum = 0;
        static bitset<maxs> msk;
        msk.reset();
        msk.set(0);
        for(int x: nums) {
            msk |= msk << x;
            sum += x;
        }
        return !(sum & 1) && msk.test(sum >> 1);
    }
};
