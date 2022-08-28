class Solution {
public:
    int countOperations(int num1, int num2) {
        int ans = 0;
        if(num1 < num2)
            swap(num1, num2);
        while(num2 > 0) {
            int q = num1 / num2;
            ans += q;
            num1 -= q * num2;
            swap(num1, num2);
        }
        return ans;
    }
};
