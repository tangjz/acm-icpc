/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
    typedef vector<NestedInteger>::const_iterator Iter;
    stack<pair<Iter, Iter> > stk;

    void adjust() {
        while(!stk.empty() && !(stk.top().first -> isInteger())) {
            pair<Iter, Iter> cur = stk.top();
            stk.pop();
            const vector<NestedInteger> &vec = cur.first -> getList();
            if((++cur.first) != cur.second)
                stk.push(cur);
            if(!vec.empty())
                stk.push(make_pair(vec.begin(), vec.end()));
        }
    }
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        stack<pair<Iter, Iter> >().swap(stk);
        if(!nestedList.empty())
            stk.push(make_pair(nestedList.begin(), nestedList.end()));
        adjust();
    }
    
    int next() {
        pair<Iter, Iter> cur = stk.top();
        stk.pop();
        int ret = cur.first -> getInteger();
        if((++cur.first) != cur.second)
            stk.push(cur);
        adjust();
        return ret;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
