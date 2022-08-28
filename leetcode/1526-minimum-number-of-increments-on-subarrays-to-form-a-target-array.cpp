class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int las = 0;
        long long ans = 0;
        for(int x : target) {
            ans += abs(x - las);
            las = x;
        }
        ans += las;
        return (int)(ans >> 1);
    }
};
