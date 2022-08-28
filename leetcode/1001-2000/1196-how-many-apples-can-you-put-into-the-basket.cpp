class Solution {
public:
    int maxNumberOfApples(vector<int>& A) {
        int ans = 0, rem = 5000;
        sort(A.begin(), A.end());
        for(int x: A) {
            if(x > rem)
                break;
            rem -= x;
            ++ans;
        }
        return ans;
    }
};
