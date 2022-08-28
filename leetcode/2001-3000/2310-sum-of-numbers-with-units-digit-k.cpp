class Solution {
public:
    int minimumNumbers(int num, int k) {
        if(!num)
            return 0;
        for(int i = 1; i <= 10; ++i) {
            int low = i * k;
            if(num >= low && num % 10 == low % 10)
                return i;
        }
        return -1;
    }
};
