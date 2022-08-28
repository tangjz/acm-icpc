class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& seq) {
        long long ans = mass;
        sort(seq.begin(), seq.end());
        for(int x: seq) {
            if(ans < x)
                return false;
            ans += x;
        }
        return true;
    }
};
