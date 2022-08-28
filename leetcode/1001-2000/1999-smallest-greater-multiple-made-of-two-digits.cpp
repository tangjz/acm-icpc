class Solution {
public:
    int findInteger(int k, int digit1, int digit2) {
        typedef long long LL;
        queue<int> que;
        if(digit1 > digit2)
            swap(digit1, digit2);
        if(!digit2)
            return -1;
        if(digit1)
            que.push(digit1);
        if(digit1 < digit2)
            que.push(digit2);
        while(!que.empty()) {
            int cur = que.front();
            que.pop();
            if(cur > k && cur % k == 0)
                return cur;
            LL pre = 10LL * cur;
            if(pre + digit1 <= INT_MAX)
                que.push(pre + digit1);
            if(digit1 < digit2 && pre + digit2 <= INT_MAX)
                que.push(pre + digit2);
        }
        return -1;
    }
};
