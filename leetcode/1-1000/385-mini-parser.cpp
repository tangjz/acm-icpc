/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
    NestedInteger parse(int L, int R, string const &s, unordered_map<int, int> &pR) {
        NestedInteger ret;
        if(s[L] != '[')
            return NestedInteger(stoi(s.substr(L, R - L + 1)));
        for(int ML = L, MR = pR[ML]; ; ML = MR, MR = pR[ML]) {
            if(ML + 1 < MR)
                ret.add(parse(ML + 1, MR - 1, s, pR));
            if(MR == R)
                break;
        }
        return ret;
    }
public:
    NestedInteger deserialize(string s) {
        int n = s.size();
        stack<int> stk;
        unordered_map<int, int> pR;
        for(int i = 0; i < n; ++i)
            if(s[i] == '[') {
                stk.push(i);
            } else if(s[i] == ']') {
                pR[stk.top()] = i;
                stk.pop();
            } else if(s[i] == ',') {
                pR[stk.top()] = i;
                stk.pop();
                stk.push(i);
            }
        return parse(0, n - 1, s, pR);
    }
};
