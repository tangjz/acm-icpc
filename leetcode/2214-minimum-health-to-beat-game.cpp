class Solution {
public:
    long long minimumHealth(vector<int>& damage, int armor) {
        int upp = 0;
        long long ans = 1;
        for(int x: damage) {
            upp = max(upp, x);
            ans += x;
        }
        ans -= min(upp, armor);
        return ans;
    }
};
