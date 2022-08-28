class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        for(int &x: nums)
            (x & 1) && (x <<= 1);
        sort(nums.begin(), nums.end());
        int ans = INT_MAX, low = nums.front();
        queue<int> que;
        while(!nums.empty() || !que.empty()) {
            int upp;
            if(que.empty() || (!nums.empty() && nums.back() > que.front())) {
                upp = nums.back();
                nums.pop_back();
            } else {
                upp = que.front();
                que.pop();
            }
            ans = min(ans, upp - low);
            while(!nums.empty() && nums.back() == upp)
                nums.pop_back();
            while(!que.empty() && que.front() == upp)
                que.pop();
            if(upp & 1)
                break;
            upp >>= 1;
            low = min(low, upp);
            que.push(upp);
        }
        return ans;
    }
};

auto fast_io = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
    return 0;
}();
