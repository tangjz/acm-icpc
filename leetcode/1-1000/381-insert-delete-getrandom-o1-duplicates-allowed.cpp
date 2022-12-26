class RandomizedCollection {
    unordered_map<int, unordered_set<int> > pos;
    vector<int> que;
    mt19937 rnd;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        unordered_map<int, unordered_set<int> >().swap(pos);
        vector<int>().swap(que);
        rnd.seed(time(NULL));
    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        auto &it = pos[val];
        it.insert((int)que.size());
        que.push_back(val);
        return (int)it.size() == 1;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        auto it = pos.find(val);
        if(it == pos.end())
            return 0;
        auto &jt = it -> second;
        int id = *jt.begin();
        if((int)jt.size() > 1) {
            jt.erase(id);
        } else {
            pos.erase(val);
        }
        int las = (int)que.size() - 1;
        if(id != las) {
            int tmp = que.back();
            auto &kt = pos[tmp];
            kt.erase(las);
            kt.insert(id);
            que[id] = tmp;
        }
        que.pop_back();
        return 1;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        int x = rnd() % (int)que.size();
        return que[x];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
