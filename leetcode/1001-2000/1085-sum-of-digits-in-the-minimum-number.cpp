class Solution {
public:
    int sumOfDigits(vector<int>& nums) {
        int val = *min_element(nums.begin(), nums.end());
        int cnt = 0;
        for(char ch: to_string(val))
            cnt += ch - '0';
        return !(cnt & 1);
    }
};
