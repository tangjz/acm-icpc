class Solution {
public:
    int minOperations(vector<string>& logs) {
        int ans = 0;
        for(auto &it : logs)
            if(it == "../") {
                ans = max(ans - 1, 0);
            } else if(it == "./") {
                
            } else {
                ++ans;
            }
        return ans;
    }
};
