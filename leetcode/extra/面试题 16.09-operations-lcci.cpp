class Operations {
public:
    Operations() {
    }

    int minus(int a, int b) {
        if(b == INT_MIN)
            return (a + 1) + INT_MAX;
        if(!b)
            return a;
        stack<long long> cand;
        cand.push(b < 0 ? 1 : -1);
        while((b + cand.top() > 0) == (b > 0))
            cand.push(cand.top() + cand.top());
        cand.pop();
        int c = a;
        while(!cand.empty()) {
            if((b + cand.top() > 0) == (b > 0)) {
                b += cand.top();
                c += cand.top();
            }
            cand.pop();
        }
        if(b)
            c += b < 0 ? 1 : -1;
        return c;
    }

    int multiply(int a, int b) {
        if(!a || !b)
            return 0;
        if(a == 1)
            return b;
        if(a == -1)
            return minus(0, b);
        if(b == 1)
            return a;
        if(b == -1)
            return minus(0, a);
        // 2 <= abs(a), abs(b) <= INT_MAX / 2
        bool neg = 0;
        if(a < 0) {
            a = minus(0, a);
            neg = !neg;
        }
        if(b < 0) {
            b = minus(0, b);
            neg = !neg;
        }
        if(a < b)
            swap(a, b);
        if(neg)
            a = minus(0, a);
        stack<pair<long long, int> > cand;
        cand.push({a, 1});
        while(cand.top().second <= b) {
            cand.push(cand.top());
            cand.top().first += cand.top().first;
            cand.top().second += cand.top().second;
        }
        cand.pop();
        int res = 0, c = 0;
        while(!cand.empty() && c < b) {
            if(c + cand.top().second <= b) {
                res += cand.top().first;
                c += cand.top().second;
            }
            cand.pop();
        }
        return res;
    }

    int divide(int a, int b) {
        if(!a)
            return 0;
        if(b == INT_MIN)
            return a == INT_MIN ? 1 : 0;
        if(b == 1)
            return a;
        if(b == -1)
            return minus(0, a);
        // abs(b) >= 2, abs(res) <= -INT_MIN / 2
        int res = 0;
        bool neg = 0;
        if(b < 0) {
            neg = !neg;
            b = minus(0, b);
        }
        if(a > 0) {
            neg = !neg;
            a = minus(0, a);
        }
        stack<pair<long long, int> > cand;
        cand.push({b, -1});
        while(cand.top().first > 0 && a + cand.top().first <= 0) {
            cand.push(cand.top());
            cand.top().first += cand.top().first;
            cand.top().second += cand.top().second;
        }
        cand.pop();
        while(!cand.empty() && a < 0) {
            if(a + cand.top().first <= 0) {
                a += cand.top().first;
                res += cand.top().second;
            }
            cand.pop();
        }
        if(neg)
            res = minus(0, res);
        return res;
    }
};

/**
 * Your Operations object will be instantiated and called as such:
 * Operations* obj = new Operations();
 * int param_1 = obj->minus(a,b);
 * int param_2 = obj->multiply(a,b);
 * int param_3 = obj->divide(a,b);
 */
