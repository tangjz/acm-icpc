class MyHashSet {
    static const int maxd = (int)1e6 + 1;
    static int tim, vis[maxd];
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        ++tim;
    }

    void add(int key) {
        vis[key] = tim;
    }

    void remove(int key) {
        vis[key] = tim - 1;
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return vis[key] == tim;
    }
};
int MyHashSet::tim, MyHashSet::vis[MyHashSet::maxd];

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
