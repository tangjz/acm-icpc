// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        int x;
        while((x = rand7() * 7 - rand7()) >= 40);
        return (x >> 2) + 1;
    }
};
