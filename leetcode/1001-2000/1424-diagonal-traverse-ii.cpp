class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<int> ret;
        priority_queue<pair<int, int> > Q;
        for(int i = 0; i < (int)nums.size(); ++i)
            if(!nums[i].empty())
                Q.push(make_pair(-i, i));
        while(!Q.empty()) {
            pair<int, int> u = Q.top();
            Q.pop();
            u.first = -u.first - u.second;
            ret.push_back(nums[u.second][u.first]);
            if((++u.first) < (int)nums[u.second].size())
                Q.push(make_pair(-(u.first + u.second), u.second));
        }
        return ret;
    }
};
