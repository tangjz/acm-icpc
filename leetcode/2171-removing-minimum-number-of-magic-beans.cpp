class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        sort(beans.begin(), beans.end());
        long long ans = 0, sum = 0, rem = beans.size();
        for(int x: beans) {
            sum += x;
            ans = min(ans, -x * rem);
            --rem;
        }
        return sum + ans;
    }
};
