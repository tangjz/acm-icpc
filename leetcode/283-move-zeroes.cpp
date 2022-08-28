class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        vector<int>::iterator it = nums.begin(), jt = nums.begin();
        for( ; jt != nums.end(); ++jt) {
            if(*jt == 0)
                continue;
            if(it == jt) {
                ++it;
            } else {
                *(it++) = *jt;
                *jt = 0;
            }
        }
    }
};
