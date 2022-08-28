class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size();
        for(int i = 0; i < n; ++i) {
            if(i == n - 1)
                return 1;
            if(bits[i])
                ++i;
        }
        return 0;
    }
};
