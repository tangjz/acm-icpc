class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = (int)nums.size();
        deque<int> que;
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            while(!que.empty() && i - que.front() >= k)
                que.pop_front();
            while(!que.empty() && nums[i] >= nums[que.back()])
                que.pop_back();
            que.push_back(i);
            if(i >= k - 1)
                ret.push_back(nums[que.front()]);
        }
        return ret;
    }
};
