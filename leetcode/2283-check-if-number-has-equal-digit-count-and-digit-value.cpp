class Solution {
public:
    bool digitCount(string num) {
        vector<int> ctr(10);
        for(char ch: num)
            ++ctr[ch - '0'];
        for(int i = 0; i < 10; ++i)
            if(ctr[i] != (i < num.size() ? num[i] - '0' : 0))
                return 0;
        return 1;
    }
};
