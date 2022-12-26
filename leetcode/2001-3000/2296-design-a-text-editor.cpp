const int maxn = (int)8e5 + 9;

class TextEditor {
    int tot;
    struct Node {
        int lch, rch;
        int key, val, sz;
    };
    vector<Node> pool;
    inline int randL() {
        return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
    }
    inline int newNode(int val) {
        if(tot == pool.size())
            pool.push_back({});
        pool[tot].key = randL();
        pool[tot].val = val;
        pool[tot].sz = 1;
        return tot++;
    }
    inline void upd(int rt) {
        int lch = pool[rt].lch, rch = pool[rt].rch;
        pool[rt].sz = pool[lch].sz + 1 + pool[rch].sz;
    }
    inline pair<int, int> split(int rt, int sz) {
        if(!rt)
            return make_pair(0, 0);
        int lch = pool[rt].lch, rch = pool[rt].rch;
        if(pool[lch].sz + 1 > sz) {
            pair<int, int> tr = split(lch, sz);
            pool[rt].lch = lch = tr.second;
            upd(rt);
            return make_pair(tr.first, rt);
        } else {
            pair<int, int> tr = split(rch, sz - pool[lch].sz - 1);
            pool[rt].rch = rch = tr.first;
            upd(rt);
            return make_pair(rt, tr.second);
        }
    }
    inline int merge(int x, int y) {
        if(!x || !y)
            return x | y;
        else if(pool[x].key < pool[y].key) {
            int rch = pool[x].rch;
            rch = merge(rch, y);
            pool[x].rch = rch;
            upd(x);
            return x;
        } else {
            int lch = pool[y].lch;
            lch = merge(x, lch);
            pool[y].lch = lch;
            upd(y);
            return y;
        }
    }

    int rt, ofs;
    string gather(int L, int R) {
        pair<int, int> t1 = split(rt, R);
        pair<int, int> t2 = split(t1.first, L);
        string ret = "";
        function<void(int)> dfs = [&](int x) {
            if(!x)
                return;
            dfs(pool[x].lch);
            ret.push_back((char)pool[x].val);
            dfs(pool[x].rch);
        };
        dfs(t2.second);
        t1.first = merge(t2.first, t2.second);
        rt = merge(t1.first, t1.second);
        return ret;
    }
public:
    TextEditor() {
        tot = 0;
        newNode(0);
        pool[0] = {};
        rt = ofs = 0;
    }

    void addText(string text) {
        int cur = 0;
        for(char ch: text)
            cur = merge(cur, newNode(ch));
        pair<int, int> t1 = split(rt, ofs);
        t1.first = merge(t1.first, cur);
        rt = merge(t1.first, t1.second);
        ofs += text.size();
        // printf("cur %d (%d): %s\n", ofs, pool[rt].sz, gather(0, pool[rt].sz).c_str());
    }

    int deleteText(int k) {
        k = min(k, ofs);
        pair<int, int> t1 = split(rt, ofs);
        pair<int, int> t2 = split(t1.first, ofs - k);
        ofs -= k;
        rt = merge(t2.first, t1.second);
        // printf("cur %d (%d): %s\n", ofs, pool[rt].sz, gather(0, pool[rt].sz).c_str());
        return k;
    }

    string cursorLeft(int k) {
        ofs = max(ofs - k, 0);
        // printf("cur %d (%d): %s\n", ofs, pool[rt].sz, gather(0, pool[rt].sz).c_str());
        return gather(max(ofs - 10, 0), ofs);
    }

    string cursorRight(int k) {
        ofs = min(ofs + k, pool[rt].sz);
        // printf("cur %d (%d): %s\n", ofs, pool[rt].sz, gather(0, pool[rt].sz).c_str());
        return gather(max(ofs - 10, 0), ofs);
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */
