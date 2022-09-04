class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int n = minutesToTest / minutesToDie + 1, ans = 0;
        for(--buckets; buckets > 0; ++ans, buckets /= n);
        return ans;
    }
};
