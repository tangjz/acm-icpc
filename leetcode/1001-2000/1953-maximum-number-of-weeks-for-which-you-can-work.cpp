class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        typedef long long LL;
        int upp = 0;
        LL sum = 0;
        for(int x: milestones) {
            upp = max(upp, x);
            sum += x;
        }
        return min(sum, (sum - upp) * 2 + 1);
    }
};
