class Solution {
public:
    bool checkPerfectNumber(int num) {
        int prd = 1;
        for(int i = 2, tmp = num; i <= tmp; ++i) {
            if(i * i > tmp)
                i = tmp;
            int sum = 1, pw = 1;
            for( ; tmp % i == 0; tmp /= i, pw *= i, sum += pw);
            if(sum > 1) {
                if(sum <= num * 2 / prd) {
                    prd *= sum;
                } else {
                    return 0;
                }
            }
        }
        return prd == num * 2;
    }
};
