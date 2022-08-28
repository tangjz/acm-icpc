class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int ans = 0;
        unordered_map<int, int> Hash;
        for(int &x : A)
            for(int &y : B)
                ++Hash[x + y];
        for(int &x : C)
            for(int &y : D) {
                auto it = Hash.find(-x - y);
                if(it != Hash.end())
                    ans += it -> second;
            }
        return ans;
    }
};
