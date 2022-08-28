class Solution {
public:
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        auto dis = [&](vector<int> const &A, vector<int> const &B) {
            return abs(A[0] - B[0]) + abs(A[1] - B[1]);
        };
        int low = dis({0, 0}, target);
        for(auto &it: ghosts)
            if(dis(it, target) <= low)
                return 0;
        return 1;
    }
};
