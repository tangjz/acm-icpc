class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        long long sum = 0;
        for(int x: chalk)
            sum += x;
        k %= sum;
        int pos = 0;
        for(int x: chalk) {
            if(k < x)
                return pos;
            ++pos;
            k -= x;
        }
        return -1;
    }
};
