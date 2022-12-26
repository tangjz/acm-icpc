class SnapshotArray {
    int n, m;
    vector<vector<pair<int, int> > > info;
public:
    SnapshotArray(int length) {
        n = length;
        m = 0;
        vector<vector<pair<int, int> > >(n).swap(info);
    }

    void set(int index, int val) {
        auto &vec = info[index];
        if(!vec.empty() && vec.back().first == m) {
            vec.back().second = val;
        } else {
            vec.push_back({m, val});
        }
    }

    int snap() {
        return m++;
    }

    int get(int index, int snap_id) {
        auto &vec = info[index];
        auto it = lower_bound(vec.begin(), vec.end(), make_pair(snap_id + 1, 0));
        if(it == vec.begin())
            return 0;
        return (--it) -> second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
